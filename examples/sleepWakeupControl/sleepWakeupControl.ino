#include "wio_tracker.h"


WioTracker wio = WioTracker();

void setup() {
  pinMode(wio.DTR_PIN, INPUT);

  SerialUSB.println("Begin...");
  wio.Power_On();
  while(false == wio.Check_If_Power_On()){
    SerialUSB.println("Waitting for module to alvie...");
    delay(1000);
  }  
  SerialUSB.println("Power On O.K!");
}

void loop() {
  SerialUSB.println("sleep...");
  while(!wio.module_sleep()){
    SerialUSB.println("Try to sleep...");
    delay(1000);    
  }
  SerialUSB.println("sleep...");
  delay(4000);
  SerialUSB.println("wakeup...");
  while(!wio.module_wakeup()){
    SerialUSB.println("Try to wakeup...");
    delay(1000);    
  }
  SerialUSB.println("wakeup...");
  delay(4000);
}