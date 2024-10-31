// pin values for Arduino
#define SIN A0
#define SQU A1

// init analog values
int val_sin = 0;
int val_squ = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:

  // read values
  val_sin = analogRead(SIN);
  val_squ = analogRead(SQU);

  char buffer[100];
  // int count = sprintf(buffer, "Sine Wave value: %f V; Square Wave value: %f\r\n", sin_f, squ_f);
  // Serial.write(buffer, count);
  
  float sin_f = (val_sin/1024.0)*5.0;
  float squ_f = (val_squ/1024.0)*5.0;
  
  Serial.print("Sine_Wave_value:");
  Serial.print(sin_f, 2);
  Serial.print(",");
  Serial.print("Square_Wave_value:");
  Serial.print(squ_f, 2);
  Serial.println("");
  delay(10); // Small delay for readability
} 
