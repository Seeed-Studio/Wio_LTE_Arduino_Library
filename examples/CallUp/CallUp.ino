#include "module_common.h"

#define RGBPIN 10

WioTracker wio = WioTracker();


void setup() {
  wio.Power_On();
  SerialUSB.println("Power On!");

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
