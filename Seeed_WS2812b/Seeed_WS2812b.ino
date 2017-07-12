#include "Seeed_ws2812.h"
#include "module_common.h"

#define LEN_NUM 1

WioTracker wio = WioTracker();
WS2812 strip = WS2812(LEN_NUM, wio.RGB_LED_PIN);


void setup() {
  // Enable VCCB
  pinMode(wio.ENABLE_VCCB_PIN, OUTPUT);
  digitalWrite(wio.ENABLE_VCCB_PIN, HIGH);
  strip.begin();
  strip.brightness = 20;
}

void loop() {  
  strip.RGBCycle(1000);   
  strip.rainbowCycle(20);	
}
