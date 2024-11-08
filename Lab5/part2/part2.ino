const int LOOPS = 1000;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600, SERIAL_8N1);
}

  float x = 1.2345;
  float y = 6.789;
void loop() {
  // put your main code here, to run repeatedly:

  unsigned long start = micros();
  for(int i = 0; i < LOOPS; i++)
  {
    x *= y;
  }
  unsigned long stop = micros();

  Serial.print("Exec Time: ");
  unsigned long val = stop - start;
  Serial.print(val, DEC);
  Serial.println();
  delay(500); // Delay to make readable
}
