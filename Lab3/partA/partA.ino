#define NUM_CHARS 27
#define MAX_MSG_SIZE 100

unsigned long lastUpdate = 0;
int index = 0;
int maxIndex = 11;
uint8_t encoded[MAX_MSG_SIZE] = "HELLO WORLD";
uint8_t decoded[MAX_MSG_SIZE] = "HELLO WORLD";
int key = 4;

void setup() {
  Serial.begin(9600, SERIAL_8N1);

  initDotDisplay();

  lastUpdate = millis();
}

void loop() {

  unsigned long diff = millis() - lastUpdate;
  if(diff > 1000)
  {
    index = (index + 1) % maxIndex;
    lastUpdate = millis();
    
#if true // Debug statement
     Serial.print("Waited ");
     Serial.print(diff, DEC);
     Serial.println("ms");
#endif
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
