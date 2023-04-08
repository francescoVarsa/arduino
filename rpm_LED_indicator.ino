#include "FastLED.h"

#define POTENTIOMETER_PIN A2
#define POTENTIOMETER_MAX 1022
#define NUM_LEDS 10
#define DATA_PIN 6
CRGB leds[NUM_LEDS];
int prevNumber = 0;
bool isAscending = true;
interva

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  Serial.begin(9600);
}

void loop() {
  int potentiometerVal = analogRead(POTENTIOMETER_PIN);
  int step = round(POTENTIOMETER_MAX / NUM_LEDS);
  int ledsToShow = round(potentiometerVal / step);
  Serial.println(ledsToShow);

  if (potentiometerVal > prevNumber) {
    isAscending = true;
  } else if (potentiometerVal < prevNumber) {
    isAscending = false;
  }

  if (ledsToShow == NUM_LEDS) {
    fill_solid(leds, NUM_LEDS, CRGB::Red);
     FastLED.show();
    delay(150);
    fill_solid(leds, NUM_LEDS, CRGB::Black);
     FastLED.show();
    delay(150);
  }

    if (isAscending) {
      for (int dot = 0; dot < ledsToShow; dot++) {
        if(dot >= 0 && dot <= 3){
        leds[dot] = CRGB::Blue;
        } else if(dot > 3  && dot <= 5){
          leds[dot] = CRGB::Yellow;
        } else if(dot > 5  && dot <= 7){
          leds[dot] = CRGB::Green;
        } else if (dot > 7){
          leds[dot] = CRGB::Red;
        }
        FastLED.show();
      }
    } else {
      for (int j = 9; j >= ledsToShow; j--) {
        leds[j] = CRGB::Black;
        FastLED.show();
      }
    }


  prevNumber = potentiometerVal;
}