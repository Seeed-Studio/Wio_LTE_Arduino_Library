#include "wio_tracker.h"

WioTracker wio = WioTracker();

void setup() {
  SerialUSB.println("Wait for power on...");
  wio.Power_On();  
  SerialUSB.println("Power On O.K!");

  while(!wio.init()){
    delay(1000);
    SerialUSB.println("Accessing network...");
  }
  SerialUSB.println("Initialize done...");

  bool ret = wio.waitForNetworkRegister();
  if(true == ret){
      SerialUSB.println("Network accessed!");
  }else {
      SerialUSB.println("Network failed!");
      return;
  }

  // Make a phone call
  wio.callUp("xxxxxxxx");
  SerialUSB.println("Calling...");

}

void loop() {
  /* Debug */
  AT_bypass();
}
