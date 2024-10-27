#define PIN_SINE A0
#define PIN_SQUARE A1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200, SERIAL_8N1);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sineRaw = analogRead(PIN_SINE);
  int squareRaw = analogRead(PIN_SQUARE);

  double sineVolt = calculateVoltage(sineRaw);
  double squareVolt = calculateVoltage(squareRaw);

  char buffer[100];
  int count = sprintf(buffer, "Sine Wave value = %f V;	Square Wave value = %f V;\r\n", sineVolt, squareVolt);
  Serial.write(buffer, count);
}

double calculateVoltage(int adcValue)
{
  const double voltPerBit = 5.0/1024;

  return adcValue * voltPerBit;
}