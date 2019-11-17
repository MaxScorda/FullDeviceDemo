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
  static long previous1 = millis();
  static long previous2 = millis();
  String stringa;
  int msStop1 = 400;
  int msStop2 = 700;
  if (previous1 + msStop1 <= millis()) {
    previous1 =  millis();
    elabKey();
    lcd.setCursor(0, 0);
    stringa = Row0.ScrollT(2);
    lcd.print(stringa);
  }
  if (previous2 + msStop2 <= millis()) {
    previous2 =  millis();
    lcd.setCursor(0, 1);
    stringa = Row1.ScrollT();
    lcd.print(stringa);
  }
}

void ScrollSegment() {
  static long previous = millis();
#define buffer_len 9
  char buffer[buffer_len];
String vars;
  int msStop = 500;
  
  if (previous + msStop <= millis()) {
    previous =  millis();
    vars=RowSegment.ScrollT();
    vars.toCharArray(buffer, buffer_len);
    module.DisplayStr(buffer, 0);
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
