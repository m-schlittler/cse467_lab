const uint8_t LED_R = 11;   // Digital 11
const uint8_t LED_G = 10;   // Digital 10
const uint8_t BTN_R = 2;    // Digital 2
const uint8_t BTN_G = 3;    // Digital 3
const uint8_t ROW_1 = 14;   // Analog A0, DD 12
const uint8_t ROW_2 = 15;   // Analog A1, DD 11
const uint8_t ROW_3 = 16;   // Analog A2, DD 02
const uint8_t ROW_4 = 17;   // Analog A3, DD 09
const uint8_t ROW_5 = 18;   // Analog A4, DD 04
const uint8_t ROW_6 = 19;   // Analog A5, DD 05
const uint8_t ROW_7 = 9;    // Digital 9, DD 06 
const uint8_t COL_1 = 4;    // Digital 4, DD 01 
const uint8_t COL_2 = 5;    // Digital 5, DD 03 
const uint8_t COL_3 = 6;    // Digital 6, DD 10
const uint8_t COL_4 = 7;    // Digital 7, DD 07
const uint8_t COL_5 = 8;    // Digital 8, DD 08
const int8_t MIN_NUM = 0;
const int8_t MAX_NUM = 9;
const uint8_t colPins[] =   { COL_1, COL_2, COL_3, COL_4, COL_5};
const uint8_t rowPins[] = { ROW_1, ROW_2, ROW_3, ROW_4, ROW_5, ROW_6, ROW_7 };
const uint8_t memBuf[10][7][5]
{
  // 0
  {
    {0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0},
  },
  // 1
  {
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0},
  },
  // 2
  {
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 1, 1, 0},
  },
  //3
  {
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0},
  },
  //4
  {
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0},
  },
  // 5
  {
    {0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0},
  },
  // 6
  {
    {0, 1, 1, 1, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 0, 0, 0},
    {0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0},
  },
  // 7
  {
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0},
  },
  // 8
  {
    {0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0},
  },
  // 9
  {
    {0, 1, 1, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 0, 0, 1, 0},
  },
};

// Current number to show
int8_t number = 0; // Do a signed number to make checks easier

// Tack how long since the last time the number has been updated
unsigned long lastChange = 0;

// Track which direction to count
bool countUp = true;

#define DEBUG 1

void setup() {
  // put your setup code here, to run once:
#if DEBUG
  Serial.begin(9600, SERIAL_8N1);
#endif

  pinMode(BTN_R, INPUT);
  pinMode(BTN_G, INPUT);

  pinMode(LED_R, OUTPUT);
  digitalWrite(LED_R, LOW);
  pinMode(LED_G, OUTPUT);
  digitalWrite(LED_G, LOW);
  
  for(uint8_t i = 0; i < 7; i++)
  {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], LOW);
  }

  for(uint8_t i = 0; i < 5; i++)
  {
    pinMode(colPins[i], OUTPUT);
    digitalWrite(colPins[i], LOW);
  }

  // Will start counting first
  number = 0;
  lastChange = millis();
  countUp = true;
  digitalWrite(LED_R, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:

  // Poll Red button
  if(!digitalRead(BTN_R))
  {
    countUp = true;
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, LOW);
  }
  // Poll Green Button
  else if(!digitalRead(BTN_G))
  {
    countUp = false;
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, HIGH);
  }
  attachInterrupt(uint8_t interruptNum, void (*userFunc)(void), int mode)

  // Check to see if enough time has elapsed for digit update
  unsigned long diff = millis() - lastChange;
  if (diff > 1000) // If at least one secoond
  {    
    if (countUp)
    {
      number = (number + 1) % (MAX_NUM + 1);
    }
    else
    {
      number = (--number < MIN_NUM) ? MAX_NUM : number;
    }
#if DEBUG
    Serial.print("Updating Number to ");
    Serial.print(number, DEC);
    Serial.print(" after waiting ");
    Serial.print(diff, DEC);
    Serial.println("ms");
#endif

    lastChange = millis();
  }

  refreshMatrix();
}

void refreshMatrix()
{
  for(int col = 0; col < 5; col++)
  {
    setRowPins(col);
    digitalWrite(colPins[col], LOW);
    delay(2);
    digitalWrite(colPins[col], HIGH);
  }
}

void setRowPins(uint8_t col)
{
  for(int row = 0; row < 7; row++)
  {
    digitalWrite(rowPins[row], memBuf[number][row][col]);
  }
}
