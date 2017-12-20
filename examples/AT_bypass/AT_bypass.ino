#include "wio_tracker.h"


WioTracker wio = WioTracker();

void setup() {
  SerialUSB.println("Begin...");
  wio.Power_On();
  while(false == wio.Check_If_Power_On()){
    SerialUSB.println("Waitting for module to alvie...");
    delay(1000);
  }  
  SerialUSB.println("Power On O.K!");
}

void loop() {
  /* Debug */
  AT_bypass();
}
