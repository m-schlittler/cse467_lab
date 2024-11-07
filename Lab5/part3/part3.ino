// Reference: https://electronoobs.com/eng_arduino_tut140.php

#define LOOPS 1
const double CLK = 16E6;

void setup() {
  // put your setup code here, to run once:
  cli();
  // Using Timer  1, just causd
  TCCR1A = 1; // TPut into normal operation
  TCCR1B = 1; // Set Clock to not use prescaler
  TCNT1 = 0; // Reset Timer value
  sei();
}

void loop() {
  // put your main code here, to run repeatedly:
  float x = 1.2345;
  float y = 6.789;

  cli();
  unsigned long start = TCNT1;
  for(int i = 0; i < LOOPS; i++)
  {
    x *= y;
  }
  unsigned long stop = TCNT1;
  sei();

  Serial.print("Exec Time: ");
  Serial.print((stop - start) / CLK, DEC);
  Serial.println();
  delay(500); // Breather for readabilty
}
