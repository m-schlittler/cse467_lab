#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// pin setup
LiquidCrystal_I2C lcd(39, 20, 4);
const uint8_t BTN_COLD = 2;   // Digital 2
const uint8_t BTN_HOT = 3;    // Digital 3
const uint8_t led = 13;       // led test

float currentTemp;
float setTemp = 20; // temp as set in ISR
bool ISRchanged = false;

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

  Serial.println("Init Done");

  // lcd setup
  lcd.init();
  lcd.backlight();
  
  // pin init
  pinMode(BTN_COLD, INPUT);
  pinMode(BTN_HOT, INPUT);
  pinMode(led, OUTPUT);

  // button interrupt
  // attachInterrupt(digitalPinToInterrupt(BTN_COLD), C_BTN, RISING); // allow for interrupt on button press
  attachInterrupt(digitalPinToInterrupt(BTN_HOT), setPoint_interrupt, RISING); // allow for interrupt on button press
}

void loop() {
  // put your main code here, to run repeatedly:
  #if true
  setColor('R');
  Serial.println("R");
  delay(1000);
  setColor('G');
  Serial.println("G");
  delay(1000);
  setColor('B');
  Serial.println("B");
  delay(1000);

  currentTemp = readTemperature();

  lcd.setCursor(0,0); // set pos for LCD
  lcd.print("Temp:");
  lcd.setCursor(6,0); // set pos for LCD
  lcd.print(currentTemp);

  Serial.print("Temp: ");
  Serial.println(currentTemp);

  if (ISRchanged) {  
    lcd.setCursor(0, 1);
    lcd.print("Setpoint:");
    lcd.setCursor(10, 1);
    lcd.print(setTemp);
    ISRchanged = false;
  }

  #endif
  delay(750);
}

void handleInterrupt()
{
  constexpr unsigned short differenceTolerance = 2;
  float difference = setTemp - currentTemp;

  // In tolerance
  if(difference < differenceTolerance)
  {
    setColor('G');
  }
  // Out of tolerance, colder
  else if(difference >= -differenceTolerance)
  {
    setColor('B');
  }
  // Out of tolerance, hotter
  else if(difference >= differenceTolerance)
  {
    setColor('R');
  }

  // Update LCD and output to serial
}


ISR(TIMER1_OVF_vect)
{
  Serial.println("A");
  //TCNT1 = 3035;
  //currentTemp = readTemperature();
  handleInterrupt();
}

// places setpoint on lcd screen
void setPoint_interrupt(){
  setTemp = currentTemp;
  ISRchanged = true;
}


