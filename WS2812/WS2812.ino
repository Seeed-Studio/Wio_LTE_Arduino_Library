#include "stm32f4_ws2812.h"
#include "wio_tracker.h"

#define LEN_NUM 1

WioTracker wio = WioTracker();
WS2812 strip = WS2812(LEN_NUM, wio.RGB_LED_PIN);

void setup() {
  // Set RGB LED power pin high
#if defined(WIO_TRACKER_LTE_V12)
  pinMode(wio.RGB_LED_PWR_PIN, OUTPUT); 
  digitalWrite(wio.RGB_LED_PWR_PIN, HIGH);
#endif
  strip.begin();
  strip.brightness = 20;
}

void loop() {  
  strip.RGBCycle(1000);   
  strip.rainbowCycle(20);
}
