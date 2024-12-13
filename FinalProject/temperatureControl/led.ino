constexpr int LED_R = 7;
constexpr int LED_G = 6;
constexpr int LED_B = 5;

void initLED()
{
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);
}

void setColor(char color)
{
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);

  color = toUpperCase(color);
  if(color == 'R')
  {
    digitalWrite(LED_R, HIGH);    
  }
  else if(color == 'G')
  {
    digitalWrite(LED_G, HIGH);    
  }
  else if(color == 'B')
  {
    digitalWrite(LED_B, HIGH);
  }
}