#define NUM_CHARS 27
#define MAX_MSG_SIZE 100

unsigned long lastUpdate = 0;
int index = 0;
int maxIndex = NUM_CHARS;

// Buffers for messages. Initialize with alphabet just to prove everything works
uint8_t encoded[MAX_MSG_SIZE] = "ABCDFEGHIJKLMNOPQRSTUVWXYZ_";
uint8_t decoded[MAX_MSG_SIZE] = "ABCDFEGHIJKLMNOPQRSTUVWXYZ_";

// Current key to the encrption algorithm
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
    index = (index + 1) % maxIndex; // Move to next character
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

// Function to read serial input and take action if data present
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
    
	// Decode message
    for (int i = 0; i < bytes; i++)
    {
      decoded[i] = decrypt(encoded[i], cypherKey);
    }
    maxIndex = bytes;
    index = 0;
	
	// Reset timer because otherwise first character is skipped
    lastUpdate = millis(); 

    // Transmit decoded message
    Serial.println("Encoded Message is:");
    Serial.write(encoded, bytes);
    Serial.println();
    Serial.println();
    Serial.println("Decoded Message is:");
    Serial.write(decoded, bytes);
    Serial.println();
    Serial.println();
  }
}

char decrypt(char c, uint8_t key)
{
  uint8_t x = c == '_' ? 26 : (c - 'A');

  x = (x + NUM_CHARS - key) % NUM_CHARS; // Add base to prevent negative number
	 
  return x == 26 ? ' ' : x + 'A';
}