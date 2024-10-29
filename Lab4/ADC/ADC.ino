// pin values for Arduino
#define SIN A0
#define SQU A1

// init analog values
float val_sin = 0;
float val_squ = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // part one -- read values
  val_sin = analogRead(SIN);
  val_squ = analogRead(SQU);

  // part three -- try with different baud rates
  // Setting a new baud rate
  Serial.flush();
  Serial.end();
  Serial.begin(115200);
  sprintf("Sine Wave value: %0.5f V; Square Wave value: %0.5f", val_sin, val_squ);
  delay(10); // Small delay for readability -- thanks GPT!
} 
