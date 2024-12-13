void initLCD()
{
  lcd.init();
  lcd.backlight();
}

void updateLCD(float currentTemp, float setTemp)
{
  lcd.clear();  // to clear previous output
    
  lcd.setCursor(1, 1);
  lcd.print("Set:");
  lcd.setCursor(6, 1);
  lcd.print(setTemp, 1);
  lcd.print(" ");
  lcd.print((char)223);
#if FAHRENHEIT
  lcd.print("F");
#else
  lcd.print("C");
#endif

  lcd.setCursor(0,0); // set pos for LCD
  lcd.print("Temp:");
  lcd.setCursor(6,0); // set pos for LCD
  lcd.print(currentTemp, 1);
  lcd.print(" ");
  lcd.print((char)223); // degree symbol
#if FAHRENHEIT
  lcd.print("F");
#else
  lcd.print("C");
#endif
}