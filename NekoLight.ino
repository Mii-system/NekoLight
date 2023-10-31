#include <FastLED.h>
#define FASTLED_FORCE_SOFTWARE_PINS

#define LED_PIN     6
#define COLOR_ORDER GRB
#define CHIPSET     WS2812B
#define NUM_LEDS    20

#define BRIGHT      64

CRGB leds[NUM_LEDS];
CRGB wleds[NUM_LEDS];

int wTBL[NUM_LEDS] = {0,1,3,6,7,8,9,5,2,4,10,12,15,19,18,17,16,13,11,14,};

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<CHIPSET , LED_PIN,GRB>(leds, NUM_LEDS);
  P99();
}

void loop() {
  CRGB  colorN(0,0,0);
  CRGB  colorR(BRIGHT,0,0);
  CRGB  colorG(0,BRIGHT,0);
  CRGB  colorB(0,0,BRIGHT);

  for(int i = 0;i < 2;i ++){
    P9(colorR);
    P9(colorG);
    P9(colorB);
  }

  for(int i = 0;i < 2;i ++){
    for(int j = 0;j < 2;j ++){  P8(colorR); }
    for(int j = 0;j < 2;j ++){  P8(colorG); }
    for(int j = 0;j < 2;j ++){  P8(colorB); }
  }

  for(int i = 0;i < 2;i ++){
    for(int j = 0;j < 2;j ++){  P6(colorR); }
    for(int j = 0;j < 2;j ++){  P6(colorG); }
    for(int j = 0;j < 2;j ++){  P6(colorB); }
  }

  for(int i = 0;i < 4;i ++){
     P5(colorR);
     P5(colorG);
     P5(colorB);
  }

  for(int i = 0;i < 2;i ++){
    for(int j = 0;j < 4;j ++){  P4(colorR); }
    for(int j = 0;j < 4;j ++){  P4(colorG); }
    for(int j = 0;j < 4;j ++){  P4(colorB); }
  }
  for(int i = 0;i < 50;i ++){
    P3();
  }
  for(int i = 0;i < 10;i ++){
    P2();
  }
  for(int i = 0;i < 5;i ++){
    P1();
  }
}

// P1	Rainbow
void P1(){
  for(int j = 0; j < 256; j+=1) {
    for(int i = 0; i < NUM_LEDS; i++) {
      wleds[i] = Scroll((i * 256 / NUM_LEDS + j) % 256);      
    }
    for(int i = 0; i < NUM_LEDS / 2; i++) {
      leds[wTBL[i]] = wleds[i];
      leds[wTBL[i + 10]] = wleds[i];
    }
    leds[4] = 0;
    leds[14] = 0;
    FastLED.show();
    delay(5);
  }
}

// WS2812B LED Strip switches Red and Green
CRGB Scroll(int pos) {
	CRGB color (0,0,0);
	if(pos < 85) {
		color.g = 0;
		color.r = ((float)pos / 85.0f) * (float)BRIGHT;
		color.b = BRIGHT - color.r;
	} else if(pos < 170) {
		color.g = ((float)(pos - 85) / 85.0f) * (float)BRIGHT;
		color.r = BRIGHT - color.g;
		color.b = 0;
	} else if(pos < 256) {
		color.b = ((float)(pos - 170) / 85.0f) * (float)BRIGHT;
		color.g = BRIGHT - color.b;
		color.r = 1;
	}
	return color;
}

// P2	ぐるぐる
void P2(){
  for(int j = 0; j < 256; j+=1) {
    for(int i = 0; i < NUM_LEDS; i++) {
      wleds[i] = Scroll2((i * 256 / NUM_LEDS + j) % 256);      
    }
    for(int i = 0; i < NUM_LEDS / 2; i++) {
      leds[wTBL[i]] = wleds[i];
      leds[wTBL[i + 10]] = wleds[i];
    }
    leds[4] = 0;
    leds[14] = 0;
    FastLED.show();
    delay(1);
  }
}

// WS2812B LED Strip switches Red and Green
CRGB Scroll2(int pos) {
	CRGB color (0,0,0);
	if(pos < 85) {
		color.g = 0;
		color.r = 0;
		color.b = BRIGHT;
	} else if(pos < 170) {
		color.g = 0;
		color.r = BRIGHT;
		color.b = 0;
	} else if(pos < 256) {
		color.b = 0;
		color.g = BRIGHT;
		color.r = 0;
	}
	return color;
}

// P3	ランダム
void P3(){
	CRGB color (0,0,0);
  color.r = random(BRIGHT);
  color.g = random(BRIGHT);
  color.b = random(BRIGHT);

  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
  FastLED.show();
  delay(100);
}

// P4	左右交互点滅
void P4(CRGB color){
  CRGB  black(0,0,0);

  for(int i = 0; i < NUM_LEDS / 2; i++) {    leds[i] = color;   }
  for(int i = NUM_LEDS / 2; i < NUM_LEDS; i++) {    leds[i] = black;    }
  FastLED.show();
  delay(200);
  for(int i = 0; i < NUM_LEDS / 2; i++) {    leds[i] = black;   }
  for(int i = NUM_LEDS / 2; i < NUM_LEDS; i++) {    leds[i] = color;    }
  FastLED.show();
  delay(200);
}

// P5	上にスクロール
void P5(CRGB color){
  CRGB  black(0,0,0);

  for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
  leds[6] = color;    leds[7] = color;    leds[8] = color;    leds[9] = color;    leds[16] = color;   leds[17] = color;   leds[18] = color;   leds[19] = color;
  FastLED.show();    delay(100);

  for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
  leds[3] = color;    leds[4] = color;    leds[5] = color;                        leds[13] = color;   leds[14] = color;   leds[15] = color;
  FastLED.show();    delay(100);

  for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
  leds[1] = color;    leds[2] = color;                                            leds[11] = color;   leds[12] = color;
  FastLED.show();    delay(100);

  for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
  leds[0] = color;                                                                leds[10] = color;
  FastLED.show();    delay(100);
}

// P6	左右スクロール
void P6(CRGB color){
  CRGB  black(0,0,0);

  for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
  leds[0] = color;    leds[1] = color;    leds[3] = color;    leds[6] = color;
  FastLED.show();    delay(50);

  for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
  leds[2] = color;    leds[4] = color;    leds[7] = color;
  FastLED.show();    delay(50);

  for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
  leds[5] = color;    leds[8] = color;
  FastLED.show();    delay(50);

  for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
  leds[9] = color;
  FastLED.show();    delay(50);

  for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
  leds[16] = color;
  FastLED.show();    delay(50);

  for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
  leds[13] = color;    leds[17] = color;
  FastLED.show();    delay(50);

  for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
  leds[11] = color;    leds[14] = color;    leds[18] = color;
  FastLED.show();    delay(50);

  for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
  leds[10] = color;    leds[12] = color;    leds[15] = color;    leds[19] = color;
  FastLED.show();    delay(50);

  // for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
  // leds[10] = color;    leds[12] = color;    leds[15] = color;    leds[19] = color;
  // FastLED.show();    delay(50);

  for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
  leds[11] = color;    leds[14] = color;    leds[18] = color;
  FastLED.show();    delay(50);

  for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
  leds[13] = color;    leds[17] = color;
  FastLED.show();    delay(50);

  for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
  leds[16] = color;
  FastLED.show();    delay(50);

  for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
  leds[9] = color;
  FastLED.show();    delay(50);

  for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
  leds[5] = color;    leds[8] = color;
  FastLED.show();    delay(50);

  for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
  leds[2] = color;    leds[4] = color;    leds[7] = color;
  FastLED.show();    delay(50);

  // for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
  // leds[0] = color;    leds[1] = color;    leds[3] = color;    leds[6] = color;
  // FastLED.show();    delay(50);
}

// P8	８の字
void P8(CRGB color){
  CRGB  black(0,0,0);
  int wTBL8[NUM_LEDS] = {9,8,7,6,3,1,0,2,5,9,16,17,18,19,15,12,10,11,13,16,};

  for(int i = 0;i < 20;i ++){
    for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
    leds[wTBL8[i]] = color;
    FastLED.show();    delay(30);
  }
}

// P9	へびパターン
void P9(CRGB color){
  CRGB  black(0,0,0);
  int wTBL8[NUM_LEDS] = {0,1,3,6,7,4,2,5,8,9,16,13,17,18,14,11,10,12,15,19,};

  for(int i = 0;i < 20;i ++){
    for(int k = 0;k < NUM_LEDS;k ++){ leds[k] = black; }
    leds[wTBL8[i]] = color;
    FastLED.show();    delay(30);
  }
}

// P10	自販機
void P10(){
}


// P11	怒り
void P11(){
}


// P12	ぬくもり
void P12(){
}


// P13	故障
void P13(){
}

// P99	LED Check
void P99(){
	CRGB color (0,0,0);

  for(int c = 0;c < 255; c++){
    color.r = c;  color.g = c;  color.b = c;
    for(int i = 0; i < NUM_LEDS; i++) {    leds[i] = color;   }
    FastLED.show();
    delay(10);
  }
  delay(2000);
  for(int c = 255;c >= 0; c--){
    color.r = c;  color.g = c;  color.b = c;
    for(int i = 0; i < NUM_LEDS; i++) {    leds[i] = color;   }
    FastLED.show();
    delay(10);
  }
}

