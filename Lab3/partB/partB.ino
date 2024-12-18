#define NUM_CHARS 27
#define MAX_MSG_SIZE 100

unsigned long lastUpdate = 0;
int index = 0;
int maxIndex = 27;

// Buffers for messages. Initialize with alphabet just to prove everything works
uint8_t encoded[MAX_MSG_SIZE] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_";
uint8_t decoded[MAX_MSG_SIZE] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ_";

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
    
	// Look for new cypher key
	// Expected format is <MSG>##
	// Where ## is the cypher shift
    int idx = 0;
    for (int i = 0; i < bytes; i++)
    {
	  // Since the cypher doesn't include numbers, can just look for that information
      if('0' <= encoded[i] && encoded[i] <= '9')
      {
        idx = i;
        break;
      }
    }

#if false
    Serial.print("IDX is ");
    Serial.print(idx, DEC);
    Serial.println();
#endif

	// get the cypher key value
    cypherKey = atoi(encoded + idx);
    
	// Decode the message
	for (int i = 0; i < idx; i++)
    {
        decoded[i] = decrypt(encoded[i], cypherKey);
      
    }

    maxIndex = idx;
    index = 0;
    lastUpdate = millis();

    // Transmit decoded message
    Serial.println("Encoded Message is:");
    Serial.write(encoded, bytes);
    Serial.println();
    Serial.println();
    Serial.println("Decoded Message is:");
    Serial.write(decoded, maxIndex);
    Serial.println();
    Serial.println();
    Serial.print("Key n is ");
    Serial.println(cypherKey, DEC);
    Serial.println();
  }
}

// Decodes the encrypted character
char decrypt(char c, uint8_t key)
{
  uint8_t x;

  if (c == '_')
  {
    x = 26;
  }
  else 
  {
    x = c - 'A';
  }

  x = (x + NUM_CHARS - key) % NUM_CHARS;
  return x == 26 ? ' ' : x + 'A';
}
