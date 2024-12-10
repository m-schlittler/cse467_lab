const int BTN_DEBOUNCE_MS = 250;

void initButtons()
{
  // pin init
  pinMode(BTN_COLD, INPUT);
  pinMode(BTN_HOT, INPUT);
  pinMode(led, OUTPUT);

  // button interrupt
  attachInterrupt(digitalPinToInterrupt(BTN_HOT), setPoint_interruptHot, FALLING); // allow for interrupt on button press
  attachInterrupt(digitalPinToInterrupt(BTN_COLD), setPoint_interruptCold, FALLING); // allow for interrupt on button press
}

// places setpoint on lcd screen
void setPoint_interruptHot(){
  //debounce vars
  static unsigned long lastPress = 0;
  if (DEBUG) {
    Serial.print("Last Hot Btn Press: ");
    Serial.println(lastPress);
  }

  if ((millis() - lastPress) > BTN_DEBOUNCE_MS) {
    lastPress = millis();

    if (DEBUG) {
      Serial.println("Increase!");
    }

    setTemp++;
    ISRchanged = true;  
  }
}

void setPoint_interruptCold(){
  //debounce vars
  static unsigned long lastPress = 0;
  if (DEBUG) {
    Serial.print("Last Cold Btn Press: ");
    Serial.println(lastPress);
  }

  if ((millis() - lastPress) > BTN_DEBOUNCE_MS) {
    lastPress = millis();
    
    if (DEBUG) {
      Serial.println("Decrease!");
    }
    
    setTemp--;
    ISRchanged = true;  
  }
}