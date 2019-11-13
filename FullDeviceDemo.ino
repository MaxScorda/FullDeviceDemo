#include <TM1638plus_Model2.h>
#include <Keypad.h> // 4X4 BUTTONS
#include <LiquidCrystal.h>

//liquidCrystal
// select the pins used on the LCD panel
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

#define  STROBE_TM 37
#define  CLOCK_TM 35
#define  DIO_TM 33

int buttonPin = 0;
unsigned long previous = 0;
boolean startbanner = true;
boolean juststart = false;
String line1= "Il pezzo d'hardware piu' inutile che abbia mai fatto. E ci sto pure a perdere tempo.";
char line2[] = " Una realizazione Cane Nico Morto Production (c) 2014 ";

//contatori
unsigned long contick = 0;
char tempTick = 0;
unsigned long prevTimer = millis();
int mainInterval;

// 4X4 BUTTONS
const byte numRows = 4; //number of rows on the keypad
const byte numCols = 4; //number of columns on the keypad
//Code that shows the the keypad connections to the arduino terminals
char keypressed ;
byte rowPins[numRows] = {40, 42, 44, 46}; //Rows 0 to 3
byte colPins[numCols] = {41, 43, 45, 47}; //Columns 0 to 3
char keymap[numRows][numCols] = {
  {'0', '1', '2', '3'},
  {'4', '5', '6', '7'},
  {'8', '9', 'A', 'B'},
  {'C', 'D', 'E', 'F'}
};
//initializes an instance of the Keypad class
Keypad myKeypad = Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);


// 4 red buttons
int selPinB4[] = { 22, 24, 26 }; // select pins on 4051 (analog A0, A1, A2)
int inPinB4[] = { 23, 25};

// 8 Led
int selLed[] = { 30, 32, 34 }; // select pins on 4051 (analog A0, A1, A2)
int outLed[] = { 31};

// TM1638 16 tasti
// define a module on data pin 8, clock pin 9 and strobe pin 7
TM1638plus_Model2 module(STROBE_TM, CLOCK_TM , DIO_TM, true);

void setup() {
  Serial.begin(9600);  // serial comms for troubleshooting (always)

  init4RedButtons();
  init8Led();
  initLiquidCrystal();
  module.reset();

  mainInterval = 1000;

}

void loop() {
  // non funziona readTM1638 e crystaldisplay
  read4RedButtons();
  Serial.print("  -   ");
  read4ExtButtons() ;
  read4x4Keypad();
  write8Led();
  scrollLiquidCrystal();
  readTM1638();

  // chiusura ciclo

  if ((prevTimer + mainInterval) <= millis()) {
    contick++;
    prevTimer = millis();
    Serial.print((String) F(" : ") +  String(contick));

  }
  Serial.println("");
}
