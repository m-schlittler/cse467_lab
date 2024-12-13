#if true

#include<Adafruit_BMP085.h>
Adafruit_BMP085 bmp;

void initTempSensor()
{
  bmp.begin();
}

float readTemperature()
{
  return bmp.readTemperature();
}

#else
#include <Wire.h>

constexpr unsigned short tempSensor_Addr = 0x77;

// Calibration parameters, using example values from documentation to pre populate
unsigned short tempSensor_AC5  = 32757;
unsigned short tempSensor_AC6  = 23153;
short tempSensor_MC  = -8711;
short tempSensor_MD  = 2868;

void initTempSensor()
{
  int lsb, msb;
  read16(tempSensor_Addr, 0xB2, &msb, &lsb);
  tempSensor_AC5 = (msb << 8) | lsb;
  read16(tempSensor_Addr, 0xB4, &msb, &lsb);
  tempSensor_AC6 = (msb << 8) | lsb;
  read16(tempSensor_Addr, 0xBC, &msb, &lsb);
  tempSensor_MC = (msb << 8) | lsb;
  read16(tempSensor_Addr, 0xBE, &msb, &lsb);
  tempSensor_MD = (msb << 8) | lsb;

  Serial.print("tempSensor_AC5: ");
  Serial.println(tempSensor_AC5);
  Serial.print("tempSensor_AC6: ");
  Serial.println(tempSensor_AC6);
  Serial.print("tempSensor_MC: ");
  Serial.println(tempSensor_MC);
  Serial.print("tempSensor_MD: ");
  Serial.println(tempSensor_MD);
}

float readTemperature()
{
  write16(tempSensor_Addr, 0xF4, 0x2E);
  Serial.println("Set to measure");
  delay(5); // Manual says to wait 4.5ms but can't do decimal so round up
  Serial.println("Done waiting");
  int msb, lsb;
  //read16(tempSensor_Addr, 0xF6, &msb, &lsb);
  Serial.println("Completed measurement");

  long UT = (msb << 8) | lsb;
  long X1 = (UT - tempSensor_AC6) * tempSensor_AC5 / (2 << 15);
  long X2 = tempSensor_MD * (2 << 11) / (X1 + tempSensor_MD);
  long B5 = X1 + X2;
  long T = (B5 + 8) / (2 << 4); // Value is in 0.1 *C
  
  return T / 10.0;
}

int write16(int address, unsigned char reg, int val)
{
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write((val >> 8) & 0xF);
  Wire.write(val & 0xF);
  return Wire.endTransmission();
}

int read16(int address, unsigned char reg, int* msb, int* lsb)
{
  int error = 0;
  *msb = *lsb = 0;
  Wire.beginTransmission(address);
  if(error == 0)
  {
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(address, 2, true);

    *msb = Wire.read();
    *lsb = Wire.read();
  }

  return error;
}
#endif