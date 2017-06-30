#include "module_common.h"
#include "Arduino_Interface.h"


WioTracker wio = WioTracker();

void setup() {
  // Enable Module Power
  pinMode(wio.MODULE_PWR_PIN, OUTPUT);
  digitalWrite(wio.MODULE_PWR_PIN , HIGH);    
  // Enable VCCB
  pinMode(wio.ENABLE_VCCB_PIN, OUTPUT);
  digitalWrite(wio.ENABLE_VCCB_PIN, HIGH);

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
  if(SerialUSB.available()){
    MODULE_PORT.write(SerialUSB.read());
  }
  if(MODULE_PORT.available()){     
    SerialUSB.write(MODULE_PORT.read()); 
  }
}
