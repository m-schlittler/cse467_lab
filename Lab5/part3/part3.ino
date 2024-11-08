// Reference: https://electronoobs.com/eng_arduino_tut140.php

const int LOOPS = 10;
const double CLK = 16E6;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600, SERIAL_8N1);
  
  cli();
  // Using Timer  1, just cause
  TCCR1A = 1; // Put into normal operation
  TCCR1B = 3; // Set Clock to  use prescaler
  TCNT1 = 0;
  sei();
}

  float x = 1.2345;
  float y = 6.789;
void loop() {
  // put your main code here, to run repeatedly:

  cli();
  unsigned long start = TCNT1 = 0;
  for(int i = 0; i < LOOPS; i++)
  {
    x *= y;
  }
  unsigned long stop = TCNT1;
  sei();

  Serial.print("Exec Time: ");
  double val = (stop - start) / CLK; 
  Serial.print(val, DEC);
  Serial.println();
  Serial.print("START: ");
  Serial.print(start, DEC);
  Serial.println();
  Serial.print("STOP: ");
  Serial.print(stop, DEC);
  Serial.println();
  delay(500); // Breather for readabilty
}
