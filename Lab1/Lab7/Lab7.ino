void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600, SERIAL_8N1);
  pinMode(11, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(11, HIGH);
  Serial.println("1");
  delay(1000);
  digitalWrite(11, LOW);
  Serial.println("0");
  delay(1000);
}