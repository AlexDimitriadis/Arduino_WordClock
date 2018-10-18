#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(100, PIN, NEO_GRB + NEO_KHZ800);

//WordClock variables
int One[] = {0,2};
int Two[] = {3,5};
int Three[] = {15,19};
int Four[] = {21,28};
int Five[] = {10,14};
int Six[] = {57,59};
int Seven[] = {6,9};
int Eight[] = {36,39};
int Nine[] = {50,54};
int Ten[] = {40,43};
int Eleven[] = {31,36};
int Twelve[] = {44,49};
int Kai[] = {60,62};
int Para[] = {65,68};
int Pente[] = {95,99};
int Deka[] = {76,79};
int Tetarto[] = {81,87};
int Eikosi[] = {70,75};
int Misi[] = {90,93};

uint32_t c =  strip.Color(40, 0, 255);

int Hour = 0;
int Min = 0;
int HourWord[2], ConnectWord[2], MinuteWord[2];

//Led fixed index  
int led[100];
int i = 0, j=0;
int offset =0;

//Digital Clock variables
//Fisrt elemenet is length
const int D_Zero[] = {12,0,1,2,10,12,20,22,30,32,40,41,42};  
const int D_One[] = {5,2,12,22,32,42};
const int D_Two[] = {11,0,1,2,12,20,21,22,30,40,41,42};
const int D_Three[] = {11,0,1,2,12,20,21,22,32,40,41,42};
const int D_Four[] = {9,0,2,10,12,20,21,22,32,42};
const int D_Five[] = {11,0,1,2,10,20,21,22,32,40,41,42};
const int D_Six[] = {12,0,1,2,10,20,21,22,30,32,40,41,42};
const int D_Seven[] = {7,0,1,2,12,22,32,42};
const int D_Eight[] = {13,0,1,2,10,12,20,21,22,30,32,40,41,42};  
const int D_Nine[] = {12,0,1,2,10,12,20,21,22,32,40,41,42};

const int Digital[] = {D_Zero,D_One,D_Two,D_Three,D_Four,D_Five,D_Six,D_Seven,D_Eight,D_Nine};
int HourFirst, HourSecond, MinFirst, MinSecond;
uint32_t HourColour =  strip.Color(0, 0, 255);
uint32_t MinuteColour =  strip.Color(255, 0, 0);

void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  //Fix led index
  for (i=0; i<10; i++) {
    j = 0;
    for (j; j<10; j++){
      if  (i%2 == 0){
        led[10*i + j] = 10*i + j;   
      }else{
        led[10*i + j] = 10*(i+1) - (j+1);
      }
    }  
  }  
}

void loop() {
//  ArrayTest();
//  Count();
  clearStrip();
 
  if (Hour == 0 | Hour == 12){ HourWord[0] = Twelve[0]; HourWord[1] = Twelve[1];}
  else if (Hour == 1 | Hour ==13) { HourWord[0] = One[0]; HourWord[1] = One[1]; }
  else if (Hour == 2 | Hour ==14) { HourWord[0] = Two[0]; HourWord[1] = Two[1]; }
  else if (Hour == 3 | Hour ==15) { HourWord[0] = Three[0]; HourWord[1] = Three[1]; }
  else if (Hour == 4 | Hour ==16) { HourWord[0] = Four[0]; HourWord[1] = Four[1]; }
  else if (Hour == 5 | Hour ==17) { HourWord[0] = Five[0]; HourWord[1] = Five[1]; }
  else if (Hour == 6 | Hour ==18) { HourWord[0] = Six[0]; HourWord[1] = Six[1]; } 
  else if (Hour == 7 | Hour ==19) { HourWord[0] = Seven[0]; HourWord[1] = Seven[1]; }
  else if (Hour == 8 | Hour ==20) { HourWord[0] = Eight[0]; HourWord[1] = Eight[1]; }
  else if (Hour == 9 | Hour ==21) { HourWord[0] = Nine[0]; HourWord[1] = Nine[1]; }
  else if (Hour == 10 | Hour == 22) { HourWord[0] = Ten[0]; HourWord[1] = Ten[1]; }
  else {
      HourWord[0] = Eleven[0]; HourWord[1] = Eleven[1];
      if (Hour == 23) Hour = -1;}
  
  if (Min <= 30) { 
    ConnectWord[0] = Kai[0]; ConnectWord[1] = Kai[1];
    if (Min <5) { MinuteWord[0] = 0; MinuteWord[1] = 0; }
    else if (Min <10) { MinuteWord[0] = Pente[0]; MinuteWord[1] = Pente[1]; }
    else if (Min <15) { MinuteWord[0] = Deka[0]; MinuteWord[1] = Deka[1]; }
    else if (Min <20) { MinuteWord[0] = Tetarto[0]; MinuteWord[1] = Tetarto[1]; }
    else if (Min <25) { MinuteWord[0] = Eikosi[0]; MinuteWord[1] = Eikosi[1]; }
    else { MinuteWord[0] = Misi[0]; MinuteWord[1] = Misi[1]; }
    }
  
  else { 
    ConnectWord[0] = Para[0]; ConnectWord[1] = Para[1];
    if (Min <5) { MinuteWord[0] = 0; MinuteWord[1] = 0; }
    else if (Min >50) { MinuteWord[0] = Pente[0]; MinuteWord[1] = Pente[1]; }
    else if (Min >45) { MinuteWord[0] = Deka[0]; MinuteWord[1] = Deka[1]; }
    else if (Min >40) { MinuteWord[0] = Tetarto[0]; MinuteWord[1] = Tetarto[1]; }
    else if (Min >35) { MinuteWord[0] = Eikosi[0]; MinuteWord[1] = Eikosi[1]; }
    }

//  showTimeText (HourWord, ConnectWord, MinuteWord, c);
  
  //Digital Mode
  HourFirst = Digital[Hour / 10];
  HourSecond = Digital[Hour % 10];
  MinFirst = Digital[Min / 10];
  MinSecond = Digital[Min % 10];
  showTimeDigital(HourFirst,HourSecond,MinFirst,MinSecond);
  
  delay(100);
//  Hour ++;
  Min ++;
  if (Min>59){Min = 0; Hour ++;}
}

void showTimeText(int HourWord[],int ConnectWord[],int MinuteWord[], uint32_t c){
  for(i=HourWord[0]; i<=HourWord[1]; i++) {
      strip.setPixelColor(i,c);      
  }
  for(i=ConnectWord[0]; i<=ConnectWord[1]; i++) {
      strip.setPixelColor(i,c);      
  }
  for(i=MinuteWord[0]; i<=MinuteWord[1]; i++) {
      strip.setPixelColor(i,c);      
  }
  strip.show();
}

void showTimeDigital(int HourFirst[], int HourSecond[], int MinFirst[], int MinSecond[]){
  //Fisrt hour digit
  for (i=1; i<=HourFirst[0]; i++){
    strip.setPixelColor(led[HourFirst[i]],HourColour);  
  }
  //Second Hour digit
  offset = 4; //4 to the right
  for (i=1; i<=HourSecond[0]; i++){
    strip.setPixelColor(led[HourSecond[i]+ offset],HourColour);  
  }
  //First Minute digit
  offset = 53; //4 to the right
  for (i=1; i<=MinFirst[0]; i++){
    strip.setPixelColor(led[MinFirst[i]+ offset],MinuteColour);  
  }
  //Second Minute digit
  offset = 57; //4 to the right
  for (i=1; i<=MinSecond[0]; i++){
    strip.setPixelColor(led[MinSecond[i]+ offset],MinuteColour);  
  }  
  strip.show();
}

void Count(){
  for (int i = 0; i<10; i++){
    clearStrip();
//    showTimeDigital(Digital[i]);
    delay(1000);
  }
}


void clearStrip(){
  for(uint16_t i=0; i<100; i++) {
      strip.setPixelColor(i, 0);
  }
  strip.show();
}

void ArrayTest(){
uint32_t c =  strip.Color(100, 100,100);
int R, B, G;
  for (i = 99; i>=0; i--){
    R = random(0,255);
    G = random(0,255);
    B = random(0,255);
    c = strip.Color(R,G,B);
    strip.setPixelColor(led[i], c);
    strip.show();
    delay(50);
  }  
}
