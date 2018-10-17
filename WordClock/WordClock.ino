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

//Led 2-D array 
int led[10][10];
int i = 0, j=0;

//Digital Clock variables
//Fisrt elemenet is length
//Hours
int H1_Zero[] = {12,0,1,2,10,12,20,22,30,32,40,41,42};  
int H1_One[] = {5,2,17,22,37,42};
int H1_Two[] = {11,0,1,2,17,20,21,22,39,40,41,42};
//int H2_Zero[] = {12,4,5,6,13,15,24,26,33,35,43,43,45};
//int H2_One[] = {5,6,13,26,33,46};
//int H2_Two[] = {12,4,5,6,13,15,24,26,33,35,43,43,45};
//int H2_Zero[] = {12,4,5,6,13,15,24,26,33,35,43,43,45};
//int H2_Zero[] = {12,4,5,6,13,15,24,26,33,35,43,43,45};


void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  //Create led 2-d Array
  for (i=0; i<10; i++) {
    j = 0;
    for (j; j<10; j++){
      if  (i%2 == 0){
        led[i][j] = 10*i + j;   
      }else{
        led[i][j] = 10*(i+1) - (j+1);
      }
    }  
  }  
}

void loop() {
//  ArrayTest();
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
 
  showTimeText (HourWord, ConnectWord, MinuteWord, c);
  delay(2000);
  Hour ++;
  Min += 5;
}

void showTimeText(int HourWord[],int ConnectWord[],int MinuteWord[], uint32_t c){
  for(int i=HourWord[0]; i<=HourWord[1]; i++) {
      strip.setPixelColor(i,c);      
  }
  for(int i=ConnectWord[0]; i<=ConnectWord[1]; i++) {
      strip.setPixelColor(i,c);      
  }
  for(int i=MinuteWord[0]; i<=MinuteWord[1]; i++) {
      strip.setPixelColor(i,c);      
  }
  strip.show();
}

void clearStrip(){
  for(uint16_t i=0; i<100; i++) {
      strip.setPixelColor(i, 0);
  }
  strip.show();
}

void ArrayTest(){
uint32_t c =  strip.Color(0, 0, 255);
 
  for (i = 0; i<10; i++){
    for (j = 0; j<10; j++){
      strip.setPixelColor(led[i][j], c);
      strip.show();
      delay(50);
      }
    }  

}
