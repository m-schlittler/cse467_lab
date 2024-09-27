const uint8_t LED_RED = 11;   // Digital 11
const uint8_t LED_GREEN = 10; // Digital 10
const uint8_t BTN_R = 2;      // Digital 2
const uint8_t BTN_G = 3;      // Digital 3
const uint8_t ROW_1 = 14;     // Analog A0, DD 12
const uint8_t ROW_2 = 15;     // Analog A1, DD 11
const uint8_t ROW_3 = 16;     // Analog A2, DD 02
const uint8_t ROW_4 = 17;     // Analog A3, DD 09
const uint8_t ROW_5 = 18;     // Analog A4, DD 04
const uint8_t ROW_6 = 19;     // Analog A5, DD 05
const uint8_t ROW_7 = 9;      // Digital 9, DD 06 
const uint8_t COL_1 = 4;      // Digital 4, DD 01 
const uint8_t COL_2 = 5;      // Digital 5, DD 03 
const uint8_t COL_3 = 6;      // Digital 6, DD 10
const uint8_t COL_4 = 7;      // Digital 7, DD 07
const uint8_t COL_5 = 8;      // Digital 8, DD 08

void setup() {
  // Debug Serial
  Serial.begin(9600, SERIAL_8N1);
  Serial.println("VERSION 1.0");
  
  // Setup LEDs
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  // Setup Buttons
  pinMode(BTN_R, INPUT);
  pinMode(BTN_G, INPUT);

  // Setup Dot Display
  pinMode(ROW_1, OUTPUT);
  pinMode(ROW_2, OUTPUT);
  pinMode(ROW_3, OUTPUT);
  pinMode(ROW_4, OUTPUT);
  pinMode(ROW_5, OUTPUT);
  pinMode(ROW_6, OUTPUT);
  pinMode(ROW_7, OUTPUT);
  pinMode(COL_1, OUTPUT);
  pinMode(COL_2, OUTPUT);
  pinMode(COL_3, OUTPUT);
  pinMode(COL_4, OUTPUT);
  pinMode(COL_5, OUTPUT);
}

void updateLEDs(uint8_t redState, uint8_t greenState){
  digitalWrite(LED_RED, redState);
  digitalWrite(LED_GREEN, greenState);
}

void getButtons() {
  uint8_t btn1 = digitalRead(BTN_R);
  uint8_t btn2 = digitalRead(BTN_G);

  Serial.print("BTN_R: ");
  Serial.print(btn1, HEX);
  Serial.print(" BTN_G: ");
  Serial.println(btn2, HEX);
}

int index = 0;

void loop() {
  updateLEDs(HIGH, LOW);
  getButtons();
  Serial.println("RED ON, GREEN OFF");
  Serial.println();
  delay(1000);

  digitalWrite(ROW_1, HIGH);
  digitalWrite(ROW_2, HIGH);
  digitalWrite(ROW_3, HIGH);
  digitalWrite(ROW_4, HIGH);
  digitalWrite(ROW_5, HIGH);
  digitalWrite(ROW_6, HIGH);
  digitalWrite(ROW_7, HIGH);
  digitalWrite(COL_1, LOW);
  digitalWrite(COL_2, LOW);
  digitalWrite(COL_3, LOW);
  digitalWrite(COL_4, LOW);
  digitalWrite(COL_5, LOW);

  updateLEDs(LOW, HIGH);
  Serial.println("RED OFF, GREEN ON");
  getButtons();
  Serial.println();
  delay(1000);

  digitalWrite(ROW_1, LOW);
  digitalWrite(ROW_2, LOW);
  digitalWrite(ROW_3, LOW);
  digitalWrite(ROW_4, LOW);
  digitalWrite(ROW_5, LOW);
  digitalWrite(ROW_6, LOW);
  digitalWrite(ROW_7, LOW);
  digitalWrite(COL_1, HIGH);
  digitalWrite(COL_2, HIGH);
  digitalWrite(COL_3, HIGH);
  digitalWrite(COL_4, HIGH);
  digitalWrite(COL_5, HIGH);
}
