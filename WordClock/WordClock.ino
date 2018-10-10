#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(100, PIN, NEO_GRB + NEO_KHZ800);
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
int Eleven[] = {31,35};
int Twelve[] = {44,49};
int Kai[] = {60,62};
int Para[] = {65,68};
uint32_t c =  strip.Color(20, 100, 250);
int Hour = 00;
int Min = 00;
void setup() {
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  clearStrip();
  if (Hour == 0 | Hour == 12){
    showNum (Twelve, c);
    if (Hour == 0) Hour= 0;
    }
  if (Hour == 1 | Hour ==13) showNum (One, c);
  if (Hour == 2 | Hour ==14) showNum (Two, c);
  if (Hour == 3 | Hour ==15) showNum (Three, c);
  if (Hour == 4 | Hour ==16) showNum (Four, c);
  if (Hour == 5 | Hour ==17) showNum (Five, c);
  if (Hour == 6 | Hour ==18) showNum (Six, c);
  if (Hour == 7 | Hour ==19) showNum (Seven, c);
  if (Hour == 8 | Hour ==20) showNum (Eight, c);
  if (Hour == 9 | Hour ==21) showNum (Nine, c);
  if (Hour == 10 | Hour == 22) showNum (Ten, c);
  if (Hour == 11 | Hour == 23) showNum (Eleven, c);
  if (Min <= 30) showNum(Kai, c);
  else showNum (Para,c);
  delay(2000);
  Hour ++;
  Min += 5;
}


void showNum(int Num[], uint32_t c){
  for(int i=Num[0]; i<=Num[1]; i++) {
      strip.setPixelColor(i,c);
      strip.show();
  }
}

void clearStrip(){
  for(uint16_t i=0; i<100; i++) {
      strip.setPixelColor(i, 0);
      strip.show();
  }

//void showSix(){
//  for(int i=57; i<=59; i++) {
//      strip.setPixelColor(i, strip.Color(200, 100, 230));
//      strip.show();
//  }
//}
//
//void showNine(){
//  for(uint16_t i=50; i<=54; i++) {
//      strip.setPixelColor(i, strip.Color(100, 200, 130));
//      strip.show();
//  }
//}
}
