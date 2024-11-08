const int LOOPS = 1000;
#define PIN 8

void setup() {
  // put your setup code here, to run once:

  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, LOW);
  // Debug to make surer I am on the correct pin
  // digitalWrite(PIN, HIGH);
  // delay(5000);
  // digitalWrite(PIN, LOW);
}
  float x = 1.2345;
  float y = 6.789;

void loop() {
  // put your main code here, to run repeatedly:

  // cli();
  // noInterrupts();
  digitalWrite(PIN, HIGH);
  for(int i = 0; i < LOOPS; i++)
  {
    x *= y;
  }
  digitalWrite(PIN, LOW);
  // interrupts();

  delay(500);
}
