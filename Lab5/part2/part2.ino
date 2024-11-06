#define LOOPS 1

void setup() {
  // put your setup code here, to run once:

  Serial.begin(96000, SERIAL_8N1);
}

void loop() {
  // put your main code here, to run repeatedly:
  float x = 1.2345;
  float y = 6.789;

  unsigned long start = micros();
  for(int i = 0; i < LOOPS; i++)
  {
    x *= y;
  }
  unsigned long stop = micros();

  Serial.print("Exec Time: ");
  Serial.print(stop - start, DEC);
  Serial.println();
  delay(500); // Delay to make readable
}
