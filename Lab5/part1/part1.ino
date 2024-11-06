#define LOOPS 1
#define PIN 1

void setup() {
  // put your setup code here, to run once:

  pinMode(PIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  float x = 1.2345;
  float y = 6.789;

  cli();
  digitalWrite(PIN, HIGH);
  for(int i = 0; i < LOOPS; i++)
  {
    x *= y;
  }
  digitalWrite(PIN, LOW);
  sei();
}
