#include <Wire.h>
#include <LiquidCrystal_I2C.h>

float currentTemp;
float setTemp = 20;

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

  Serial.println("Init Timer");
  TCCR1A = 0;
  TCCR1B = 0;
  TCCR1B |= 0x04;
  TCNT1 = 3035;
  TIMSK1 |= 0x01;

  Serial.println("Init Done");
}

void loop() {
  // put your main code here, to run repeatedly:
  #if false
  setColor('R');
  Serial.println("R");
  delay(1000);
  setColor('G');
  Serial.println("G");
  delay(1000);
  setColor('B');
  Serial.println("B");
  delay(1000);

  float temp = readTemperature();
  Serial.print("Temp: ");
  Serial.println(temp);
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



