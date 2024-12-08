#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// pin setup
LiquidCrystal_I2C lcd(39, 20, 4);
const uint8_t BTN_COLD = 3;   // Digital 2
const uint8_t BTN_HOT = 2;    // Digital 3
const uint8_t led = 13;       // led test

// varaible setup
#define DEBUG true

float currentTemp;
float setTemp; // temp as set in ISR
bool ISRchanged = true; // Initially true to allow value to be shown
bool readTemp = true; // timer based temp RT update

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600, SERIAL_8N1);
  Serial.println("Init Start");
#define BMP085_DEBUG 1
  Serial.println("Init I2C");
  Wire.begin();

  Serial.println("Init TempSensor");
  initTempSensor();

  Serial.println("Init LED");
  initLED();

  // Serial.println("Init Timer");
  // TCCR1A = 0;
  // TCCR1B = 0;
  // TCCR1B |= 0x04;
  // TCNT1 = 3035;
  // TIMSK1 |= 0x01;

  // Timer Generated Code: 1s TIMER1 OVF
  TCCR1A = 0;           // Init Timer1A
  TCCR1B = 0;           // Init Timer1B
  TCCR1B |= B00000100;  // Prescaler = 256
  TCNT1 = 3035;         // Timer Preloading
  TIMSK1 |= B00000001;  // Enable Timer Overflow Interrupt

  Serial.println("Init Done");

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
  // attachInterrupt(digitalPinToInterrupt(BTN_COLD), C_BTN, RISING); // allow for interrupt on button press
  attachInterrupt(digitalPinToInterrupt(BTN_HOT), setPoint_interruptHot, RISING); // allow for interrupt on button press
  attachInterrupt(digitalPinToInterrupt(BTN_COLD), setPoint_interruptCold, RISING); // allow for interrupt on button press
}

void loop() {
  // put your main code here, to run repeatedly:
  #if true
  // setColor('R');
  // Serial.println("R");
  // delay(1000);
  // setColor('G');
  // Serial.println("G");
  // delay(1000);
  // setColor('B');
  // Serial.println("B");
  // delay(1000);
 
  if (readTemp) { // update
    currentTemp = readTemperature();
    tempCheckLED();

    lcd.setCursor(0,0); // set pos for LCD
    lcd.print("Temp:");
    lcd.setCursor(6,0); // set pos for LCD
    lcd.print(currentTemp, 1);
    lcd.print(" ");
    lcd.print((char)223);
    lcd.print("C");

    Serial.print("Temp: ");
    Serial.println(currentTemp);
    
    readTemp = false;
  }

  if (ISRchanged) {  
    lcd.setCursor(1, 1);
    lcd.print("Set:");
    lcd.setCursor(6, 1);
    lcd.print(setTemp, 1);
    lcd.print(" ");
    lcd.print((char)223);
    lcd.print("C");
    ISRchanged = false;
  }

  #endif
  // delay(750);

  
}

// void handleInterrupt()
// {
//   constexpr unsigned short differenceTolerance = 2;
//   float difference = setTemp - currentTemp;

//   // In tolerance
//   if(difference < differenceTolerance)
//   {
//     setColor('G');
//   }
//   // Out of tolerance, colder
//   else if(difference >= -differenceTolerance)
//   {
//     setColor('B');
//   }
//   // Out of tolerance, hotter
//   else if(difference >= differenceTolerance)
//   {
//     setColor('R');
//   }

//   // Update LCD and output to serial
// }


ISR(TIMER1_OVF_vect)
{
  TCNT1 = 3035; // Timer Preloading
  readTemp = true; 
}

// places setpoint on lcd screen
void setPoint_interruptHot(){
  //debounce vars
  static unsigned long lastPress = 0;

  if ((millis() - lastPress) > 1000) {
    lastPress = millis();

    setTemp++;
    Serial.println("Increase!");
    ISRchanged = true;  
  }
}

void setPoint_interruptCold(){
  //debounce vars
  static unsigned long lastPress = 0;

  if ((millis() - lastPress) > 1000) {
    lastPress = millis();
    
    setTemp--;
    Serial.println("decrease!");
    ISRchanged = true;  
  }
}

void tempCheckLED() {
  float diff = currentTemp - setTemp;

  if (diff > 1) { // need to cool
    setColor('B');
    Serial.println("B");
  }
  else if (diff < -1) { // need to heat
    setColor('R');
    Serial.println("R");
  }
  else { // temp is good
    setColor('G');
    Serial.println("G");
  }
}
