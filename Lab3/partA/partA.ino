// Constants for manipulating the dot dispaly matrix
#define ROW_1 14   // Analog A0, DD 12
#define ROW_2 15   // Analog A1, DD 11
#define ROW_3 16   // Analog A2, DD 02
#define ROW_4 17   // Analog A3, DD 09
#define ROW_5 18   // Analog A4, DD 04
#define ROW_6 19   // Analog A5, DD 05
#define ROW_7 9    // Digital 9, DD 06 
#define COL_1 4    // Digital 4, DD 01 
#define COL_2 5    // Digital 5, DD 03 
#define COL_3 6    // Digital 6, DD 10
#define COL_4 7    // Digital 7, DD 07
#define COL_5 8    // Digital 8, DD 08
const uint8_t colPins[] =   { COL_1, COL_2, COL_3, COL_4, COL_5};
const uint8_t rowPins[] = { ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7 };

#define NUM_CHARS 27
#define KEY 4

unsigned long lastUpdate = 0;
uint8_t index = 0;
String encoded = "";
String decoded = "";

void setup() {
  Serial.begin(9600, SERIAL_8N1);

  for(int i = 0; i < 5; i++)
  {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], LOW);
  }

  for(int i = 0; i < 7; i++)
  {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW);
  }

  lastUpdate = millis();
}

void loop() {

  unsigned long diff = millis() - lastUpdate;
  if(diff > 1000)
  {
    index = (index + 1) % 27;
    lastUpdate = millis();
    // Serial.println(alphabet[index]);
  }

  refreshMatrix();
}

char decrypt(char c, uint8_t key)
{
  return (c - key + 27) % 27;
}

char encrypt(char c, uint8_t key)
{
  return (c + key) % 27;
}
