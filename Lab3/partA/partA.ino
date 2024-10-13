#define NUM_CHARS 27
#define MAX_MSG_SIZE 100

unsigned long lastUpdate = 0;
int index = 0;
int maxIndex = 11;
uint8_t encoded[MAX_MSG_SIZE] = "HELLO WORLD";
uint8_t decoded[MAX_MSG_SIZE] = "HELLO WORLD";
int cypherKey = 4;

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
    
#if false // Debug statement
     Serial.print("Waited ");
     Serial.print(diff, DEC);
     Serial.println("ms");
#endif
  }

  refreshMatrix();

  processSerial();
}

void processSerial()
{
  if(Serial.available() > 0)
  {
    // Clear past message
    for(int i=0; i<MAX_MSG_SIZE; i++)
    {
      encoded[i] = decoded[i] = '\0';
    }
    // Read an entire line of text
    size_t bytes = Serial.readBytesUntil('\n', encoded, MAX_MSG_SIZE);
    
    for (int i = 0; i < bytes; i++)
    {
      decoded[i] = decrypt(encoded[i], cypherKey);
    }
    maxIndex = bytes;
    index = 0;

    // Transmit decoded message
    Serial.write(decoded, bytes);
    // Serial.write("H".toChar(), DEC);
    Serial.write('\n');
  }
}

char decrypt(char c, uint8_t key)
{
  uint8_t x;

  if (c == '_')
  {
    x = 26;
    // return (26 - key + 27) % 27;
  }
  else {
    x = c - 'A';
    // return (c - key + 27) % 27;
  }
     x = (x + 27 - key) % 27;
     return x == 26 ? ' ' : x + 'A';
}

char encrypt(char c, uint8_t key)
{
  return (c + key) % 27;
}
