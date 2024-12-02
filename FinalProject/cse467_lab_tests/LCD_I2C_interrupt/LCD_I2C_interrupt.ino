// include the library code:
#include <LiquidCrystal_I2C.h>
// #include <TimerOne.h>

#define DEBUG false;

// pin setup
LiquidCrystal_I2C lcd(39, 20, 4);
const uint8_t BTN_COLD = 2;    // Digital 2
const uint8_t BTN_HOT = 3;    // Digital 3
const uint8_t led = 13;

unsigned long n = 0;
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
  // put your setup code here, to run once:
  // if (DEBUG) {
  Serial.begin(9600); // see outputs on Serial Monitor
  // }

  lcd.init();
  lcd.backlight();
  
  show_current_temp();

  pinMode(BTN_COLD, INPUT);
  pinMode(BTN_HOT, INPUT);
  pinMode(led, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(BTN_COLD), C_BTN, RISING); // allow for interrupt on button press
  attachInterrupt(digitalPinToInterrupt(BTN_HOT), H_BTN, RISING); // allow for interrupt on button press
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(led, HIGH);
  delay(2000);
  digitalWrite(led, LOW);
  delay(2000);
}

void debounce(String btn_color) {
  // read the state of the switch into a local variable:
  int reading;
  
  if (btn_color == "B"){
    int reading = digitalRead(BTN_COLD);  
    buttonState = digitalRead(BTN_COLD);
  }
  else if (btn_color == "R") {
    int reading = digitalRead(BTN_HOT);
    buttonState = digitalRead(BTN_HOT);
  }
  // else {
  //   return;
  // }

  // Serial.print("Reading: ");
  // Serial.println(reading);

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

void C_BTN() {

  debounce("B");
  
  // Timer1.detachInterrupt();

  // if (DEBUG) {
  //   Serial.print("Is button pressed (validly)? ");
  //   Serial.println(buttonPressed);
  // }

  if (buttonPressed) {
    lcd.clear();

    // we set a threshold so that the house doesn't get too cold!!
    if (new_temp >= 60) {
      new_temp--;

      lcd.setCursor(0, 0);
      lcd.print("New Temp:");
      lcd.setCursor(10, 0);
      lcd.print(new_temp);

      // Timer1.start();
      // Timer1.attachInterrupt(show_current_temp);
    }

    else { 
      lcd.setCursor(0, 1);
      lcd.print("Min Temp Reached!");
    }

    // if (DEBUG) {
    Serial.print("Colder! Temp lowered to: ");
    Serial.println(new_temp);
    // }
    // buttonPressed = false;
  }
}

void H_BTN() {
  // Serial.println("HOT Entered!");
  // debounce("R");
  // Serial.println("Back into HOT from Debounce!");
  // // Timer1.detachInterrupt();

  // // if (DEBUG) {
  // //   Serial.print("Is button pressed (validly)? ");
  // //   Serial.println(buttonPressed);
  // // }

  // if (buttonPressed) {
  //   Serial.println("HOT Button Pressed!");
  //   lcd.clear();
  //   // we set a threshold so that the house doesn't get too cold!!
  //   if (new_temp <= 80) {
  //     new_temp++;

  //     lcd.setCursor(0, 0);
  //     lcd.print("New Temp:");
  //     lcd.setCursor(10, 0);
  //     lcd.print(new_temp);

  //     // Timer1.start();
  //     // Timer1.attachInterrupt(show_current_temp);
  //   }

  //   else { 
  //     lcd.setCursor(0, 1);
  //     lcd.print("Max Temp Reached!");
  //   }


  //   // if (DEBUG) {
  //   Serial.print("Hotter! Temp raised to: ");
  //   Serial.println(new_temp);
  //   // }
  //   buttonPressed = false;
  //   delay(1000);
  // }
  // Serial.print(n++);
}