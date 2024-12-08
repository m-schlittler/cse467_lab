#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// pin setup
LiquidCrystal_I2C lcd(39, 20, 4);
const uint8_t BTN_COLD = 3;   // Digital 2
const uint8_t BTN_HOT = 2;    // Digital 3
const uint8_t led = 13;       // led test

// varaible setup
#define DEBUG true

float currentTemp; // temp as read by thermo sensor
float setTemp; // temp as set in ISR
bool ISRchanged = true; // Initially true to allow value to be shown
bool readTemp = true; // timer based temp Real-Time update

void setup() {

  if (DEBUG) {
    Serial.begin(9600, SERIAL_8N1);
    Serial.println("Init Start");
  }

  if (DEBUG) {
    Serial.println("Init I2C");
  }
  
  Wire.begin();

  if (DEBUG){
    Serial.println("Init TempSensor");
  }
  initTempSensor();

  if (DEBUG) {
    Serial.println("Init LED");
  }
  initLED();

  if (DEBUG) {
    Serial.println("Init Timer");
  }
  
  // Timer Generated Code: 1s TIMER1 OVF
  TCCR1A = 0;           // Init Timer1A
  TCCR1B = 0;           // Init Timer1B
  TCCR1B |= B00000100;  // Prescaler = 256
  TCNT1 = 3035;         // Timer Preloading
  TIMSK1 |= B00000001;  // Enable Timer Overflow Interrupt

  if (DEBUG) {
    Serial.println("Init Done");
  }
  
  // lcd setup
  lcd.init();
  lcd.backlight();
  
  // pin init
  pinMode(BTN_COLD, INPUT);
  pinMode(BTN_HOT, INPUT);
  pinMode(led, OUTPUT);

  // setpoint to curent reading
  setTemp = readTemperature();
  setTemp = floor(setTemp);

  // button interrupt
  attachInterrupt(digitalPinToInterrupt(BTN_HOT), setPoint_interruptHot, RISING); // allow for interrupt on button press
  attachInterrupt(digitalPinToInterrupt(BTN_COLD), setPoint_interruptCold, RISING); // allow for interrupt on button press
}

void loop() {

  if (ISRchanged || readTemp) {
    currentTemp = readTemperature();
    tempCheckLED();

    lcd.clear();  // to clear previous output
    
    lcd.setCursor(1, 1);
    lcd.print("Set:");
    lcd.setCursor(6, 1);
    lcd.print(setTemp, 1);
    lcd.print(" ");
    lcd.print((char)223);
    lcd.print("C");

    lcd.setCursor(0,0); // set pos for LCD
    lcd.print("Temp:");
    lcd.setCursor(6,0); // set pos for LCD
    lcd.print(currentTemp, 1);
    lcd.print(" ");
    lcd.print((char)223); // degree symbol
    lcd.print("C");

    if (DEBUG) {
      Serial.print("Temp: ");
      Serial.println(currentTemp);
      Serial.print("Set Temp: ");
      Serial.println(setTemp);
    }

    readTemp = false;
    ISRchanged = false;
  }

  
}

// timer interrupt for RT temp updates
ISR(TIMER1_OVF_vect) 
{
  TCNT1 = 3035; // Timer Preloading
  readTemp = true; 
}

// places setpoint on lcd screen
void setPoint_interruptHot(){
  //debounce vars
  static unsigned long lastPress = 0;
  if (DEBUG) {
    Serial.print("Last Hot Btn Press: ");
    Serial.println(lastPress);
  }

  if ((millis() - lastPress) > 1000) {
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

  if ((millis() - lastPress) > 1000) {
    lastPress = millis();
    
    if (DEBUG) {
      Serial.println("Decrease!");
    }
    
    setTemp--;
    ISRchanged = true;  
  }
}

void tempCheckLED() {
  float diff = currentTemp - setTemp;

  if (diff > 1) { // need to cool
    setColor('B');
    
    if (DEBUG) {
      Serial.println("B");
    }
    
  }
  else if (diff < -1) { // need to heat
    setColor('R');
    
    if (DEBUG) {
      Serial.println("R");
    }
    
  }
  else { // temp is good
    setColor('G');
    
    if (DEBUG) {
      Serial.println("G");
    }
  }
}
