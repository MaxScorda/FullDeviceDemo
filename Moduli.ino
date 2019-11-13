void read4RedButtons() {
  // 4 red buttons
  for (int i = 0; i < 4; i++) {
    digitalWrite(selPinB4[0], bitRead(i , 0));
    digitalWrite(selPinB4[1], bitRead(i , 1));
    digitalWrite(selPinB4[2], 0);
    Serial.print(String(digitalRead(inPinB4[0])) + " ");
  }
}

void read4ExtButtons() {
  // ext buttons
  // si suppone siano attacati ai pin 4-7 del mux
  for (int i = 0; i < 4; i++) {
    digitalWrite(selPinB4[0], !bitRead(i , 0));
    digitalWrite(selPinB4[1], !bitRead(i , 1));
    digitalWrite(selPinB4[2], 1);
    Serial.print(String(digitalRead(inPinB4[0])) + " ");
  }
}

void read4x4Keypad() {
  // 4 x4 keypad
  keypressed = myKeypad.getKey();
  if (keypressed != NO_KEY) Serial.print(" -  " + String(keypressed) + " -");
}

void write8Led() {
  // 8 Led
  tempTick = (contick % 8);
  digitalWrite(selLed[0], bitRead(tempTick, 0));
  digitalWrite(selLed[1], bitRead(tempTick, 1));
  digitalWrite(selLed[2], bitRead(tempTick, 2));
  digitalWrite(outLed[0], false);

}

void readTM1638() {
  unsigned char buttons = module.ReadKey16();
#define buffer_len 9
  char buffer[buffer_len];
  String vars;

  if (buttons)  {
    Serial.println(buttons);
    vars = padS(String(buttons), 8, " ");
    vars.toCharArray(buffer, buffer_len);
    module.DisplayStr(buffer, 0);
    //module.DisplayDecNum(buttons, 0, false);
  }

}

//-------------liquid crystal
void scrollLiquidCrystal() {
  static long previous = millis();
  int msStop = 500;
  if (previous + msStop <= millis()) {
    previous =  millis();
    elabKey();
    lcd.setCursor(0, 0); 
    lcd.print( ScrollFunction(line1, 0));
    //if (startbanner == true)  pos2 = scrollLineAuto(line2, 1, pos2);
  }
}

void elabKey() {
  lcd.setCursor(0, 1);           // move to the begining of the second line
  lcd_key = read_LCD_buttons();  // read the buttons

  switch (lcd_key) {              // depending on which button was pushed, we perform an action
    case btnRIGHT:
      lcd.print(F("RIGHT "));
      Serial.println("RIGHT ");
      break;
    case btnLEFT:
      lcd.print(F("LEFT   "));
      Serial.println(F("LEFT "));
      break;
    case btnUP:
      lcd.print(F("UP    "));
      Serial.println(F("UP "));
      break;
    case btnDOWN:
      lcd.print(F("DOWN  "));
      Serial.println(F("DOWN "));
      break;
    case btnSELECT:
      //   lcd.print(F("SELECT"));
      Serial.println(F("SELECT "));
      break;
    case btnNONE:
      // lcd.print("NONE  ");
      break;
  }
}

// read the buttons
int read_LCD_buttons() {
  adc_key_in = analogRead(0);      // read the value from the sensor

  if (adc_key_in < 60)   return btnRIGHT;
  else if (adc_key_in < 200) return btnUP;
  else if (adc_key_in < 400) return btnDOWN;
  else if (adc_key_in < 550) return btnLEFT;
  else if (adc_key_in < 800) return btnSELECT;
  else if (adc_key_in > 800) return btnNONE;

  return btnNONE;  // when all others fail, return this...
}

int scrollLineAuto(char* lline, int riga, int ppos) {
  //Check if the current second since restart is a mod of refresh seconds ,
  //if it is then update the display , it must also not equal the previously
  //stored value to prevent duplicate refreshes
  char lcdTop[17];//Create a char array to store the text for the line
  int copySize = 16; // What is the size of our screen , this could probably be moved outside the loop but its more dynamic like this
  int tempPos = ppos;
  lcd.setCursor(0, riga);//Set our draw position , set second param to 0 to use the top line

  if (strlen(lline) < 16)
  {
    //if the message is bigger than the current buffer use its length instead;
    copySize = strlen(lline);
  }
  //Store the current position temporarily and invert its sign if its negative since we are going in reverse

  if (tempPos < 0)
  {
    tempPos = -(tempPos);
  }
  //Build the lcd text by copying the required text out of our template message variable
  memcpy(&lcdTop[0], &lline[tempPos], copySize);
  lcd.print(lcdTop);//Print it from position 0
  //Increase the current position and check if the position + 16 (screen size) would be larger than the message length , if it is go in reverse by inverting the sign.
  ppos += 1;

  if (ppos + 16 >= (int)strlen(lline))
  {
    ppos = -(ppos);
  }
  return ppos;
}

String ScrollFunction(String lline, int riga) {
    int copySize = 16;
    static int ppos = copySize;
    static String stToPrnt = " " + lline.substring(1, copySize);

    ppos = ppos % lline.length();
    stToPrnt = stToPrnt.substring(2, copySize) + lline.substring(ppos + 1, 1);
    ppos++;

    return stToPrnt;

}
