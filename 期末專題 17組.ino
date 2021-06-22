#define C3 131
#define D3 147
#define E3 165
#define F3 175
#define G3 196
#define A3 220
#define B3 247
#define C4 262

int latchPin = 8;
int clockPin = 12;
int dataPin = 11;
    
byte colDataMatrix[8]={
  B11111110,
  B11111101,
  B11111011,
  B11110111,
  B11101111,
  B11011111,
  B10111111,
  B01111111};
byte a[8]={
  B00000001,
  B00000010,
  B00000100,
  B00001000,
  B00010000,
  B00100000,
  B01000000,
  B10000000}; 

byte previousState[8]={1};
long note[] = {131,147,165,175,196,220,247,262};
byte buttonPin[] = {7,6,5,4,3,2,1,0};
byte count = 0;
byte butState[8]={1};
void setup()
{
  pinMode(latchPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  for(byte i=0;i<8;i++)
  {
    pinMode(buttonPin[i],INPUT_PULLUP);
  }
}

void loop()
{  
  for(byte p=0;p<8;p++) 
  {
    butState[p] = digitalRead(buttonPin[p]);
  }
  for(byte i=0;i<8;i++)
  { 
    if (butState[i] == 0)
    {
      if(count>7){count = 0;}
      tone(9,note[i],150);
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,MSBFIRST,colDataMatrix[i]);
      shiftOut(dataPin,clockPin,MSBFIRST,a[count]);
      digitalWrite(latchPin,HIGH);      
      delay(200);
      count++;
      previousState[i]=0;
     }
  }
  for(int i=0;i<8;i++)
  {
    if(butState[i]==1&& previousState[i]==0)
    {
      noTone(9);
      previousState[i]=1;
    }
  }
}    

