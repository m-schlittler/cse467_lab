#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP085.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
Adafruit_BMP085 bmp;

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("Hello, World!");

  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);

  Serial.begin(9600, SERIAL_8N1);
  if(!bmp.begin())
  {
    Serial.println("Error starting temperature sensor");
    while(true) {}
  }
}

int pin = 5;
void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Temp = ");
  Serial.print(bmp.readTemperature(), 1);
  Serial.println(" *C");

  for (int i = 5; i <= 7; i++)
  {
    digitalWrite(i, LOW);
  }
  digitalWrite(pin++, HIGH); 
  if(pin > 7) {pin = 5;}

  delay(5000);
}
