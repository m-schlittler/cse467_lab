// include the library code:
#include <LiquidCrystal.h>
#include <TimerOne.h>

#define DEBUG true

// pin & device setups
const int BTN_B = 3, BTN_R = 2;    // buttons tied to Digitals 2 & 3 for interrupts
const int rs = 13, en = 12, d4 = 7, d5 = 6, d6 = 5, d7 = 4; // LCD config
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// variables for tracking, testing, and control
volatile unsigned long current_temp = 70, new_temp = current_temp; // testing temp
const unsigned long FIVE_SEC = 5000000; // in terms of microseconds for Timer1 lib

int buttonState;            // the current reading from the input pin
int lastButtonState = LOW;  // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// the following variables are volatile as they are shared between processes
volatile unsigned long lastTempTime = 0; // last time current temperature reading changed
volatile unsigned long tempDelay = 2000; // reading time interval

volatile bool buttonPressed = false;
volatile bool interruptOccurred = false;

void setup() {
  if (DEBUG) {
    Serial.begin(9600); // see outputs on Serial Monitor
  }

  lcd.begin(16, 2);
  show_current_temp(); 

  pinMode(BTN_B, INPUT);
  pinMode(BTN_R, INPUT);
  
  Timer1.initialize(FIVE_SEC); // init timer interrupt to be five second period
  attachInterrupt(digitalPinToInterrupt(BTN_B), C_BTN, RISING); // allow for interrupt on button press
  attachInterrupt(digitalPinToInterrupt(BTN_R), H_BTN, RISING); // allow for interrupt on button press

}

void loop() {
  // if (DEBUG) {
  //   Serial.print("Reading: ");
  //   Serial.println(digitalRead(BTN_B));
  // }
  // delay(1000);
}

void debounce(String btn_color) {
  // read the state of the switch into a local variable:
  int reading;
  
  if (btn_color == "B"){
    int reading = digitalRead(BTN_B);  
    buttonState = digitalRead(BTN_B);
  }
  else if (btn_color == "R") {
    int reading = digitalRead(BTN_R);
    buttonState = digitalRead(BTN_R);
  }
  else {
    return;
  }

  Serial.print("Reading: ");
  Serial.println(reading);

  // if (DEBUG) {
  //   Serial.print("Reading: ");
  //   Serial.print(reading);
  //   Serial.print(" ButtonState: ");
  //   Serial.println(buttonState);
  // }
  
  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    // if (DEBUG) {
    //   Serial.print("Diff: ");
    //   Serial.println(millis() - lastDebounceTime);
    // }
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      buttonPressed = true;
    }
  }

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}

// output current temperature
void show_current_temp() {

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.setCursor(6, 0);
  lcd.print(current_temp);
  
  // have current_temp steadily decrease to match temp
  if (new_temp != current_temp) {
    
    if ((millis() - lastTempTime) > tempDelay) {
      if (new_temp < current_temp) { // Need to cool
        current_temp--;
      } 
      else if (new_temp > current_temp) { // Need to heat
        current_temp++;
      }

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp:");
      lcd.setCursor(6, 0);
      lcd.print(current_temp);
    }

    lastTempTime = millis();
  
  }
}

// have LCD decrement temperature and set after 5 seconds of waiting
void C_BTN() {

  debounce("B");
  
  Timer1.detachInterrupt();

  if (DEBUG) {
    Serial.print("Is button pressed (validly)? ");
    Serial.println(buttonPressed);
  }

  if (buttonPressed) {
    lcd.clear();

    // we set a threshold so that the house doesn't get too cold!!
    if (new_temp >= 60) {
      new_temp--;

      lcd.setCursor(0, 0);
      lcd.print("New Temp:");
      lcd.setCursor(10, 0);
      lcd.print(new_temp);

      Timer1.start();
      Timer1.attachInterrupt(show_current_temp);
    }

    else { 
      lcd.setCursor(0, 1);
      lcd.print("Min Temp Reached!");
    }

    if (DEBUG) {
      Serial.print("Colder! Temp lowered to: ");
      Serial.println(new_temp);
    }
    // buttonPressed = false;
  }
}

// have LCD increment temperature and set after 5 seconds of waiting
void H_BTN() {

  debounce("R");

  Timer1.detachInterrupt();

  if (DEBUG) {
    Serial.print("Is button pressed (validly)? ");
    Serial.println(buttonPressed);
  }

  if (buttonPressed) {
    lcd.clear();

    // we set a threshold so that the house doesn't get too cold!!
    if (new_temp <= 80) {
      new_temp++;

      lcd.setCursor(0, 0);
      lcd.print("New Temp:");
      lcd.setCursor(10, 0);
      lcd.print(new_temp);

      Timer1.start();
      Timer1.attachInterrupt(show_current_temp);
    }

    else { 
      lcd.setCursor(0, 1);
      lcd.print("Max Temp Reached!");
    }

    if (DEBUG) {
      Serial.print("Hotter! Temp raised to: ");
      Serial.println(new_temp);
    }
    // buttonPressed = false;
  }
}