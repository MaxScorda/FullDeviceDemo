void init4RedButtons() {
  //  4 red buttons
  for (int i = 0; i < 3; i++) { // out
    pinMode(selPinB4[i], OUTPUT);
  }
  for (int i = 0; i < 1; i++) { // in
    pinMode(inPinB4[i], INPUT);
    digitalWrite(inPinB4[i], HIGH);
  }
}

void init8Led() {
  //  8 Led
  for (int i = 0; i < 3; i++) { // out
    pinMode(selLed[i], OUTPUT);
  }
  for (int i = 0; i < 1; i++) { // in
    pinMode(outLed[i], OUTPUT);
  }
}

void initLiquidCrystal() {
  lcd.begin(16, 2);              // start the library
  lcd.setCursor(0, 0);
  lcd.print("Ready"); // print a simple message
  pinMode(buttonPin, INPUT);
}

String padS(String sstt, int lens, String charsub) {
  String spaces = "";
  for (int i = sstt.length(); i < lens; i++) spaces = spaces + charsub;
  return spaces+sstt;
}
