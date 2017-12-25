#include "wio_tracker.h"

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

}
void loop() {
  int rssi;
  wio.getSignalStrength(&rssi);
  SerialUSB.print("RSSI: ");
  SerialUSB.print(rssi);
  SerialUSB.print(" ");
   
  if(rssi == 99) {
    rssi = 9999;
  }
  else if(rssi == 0) {
    rssi = -113;
  }
  else if(rssi == 1) {
    rssi = -111;
  }
  else if(rssi >= 2 && rssi <= 30) {
    rssi = -109 + 2*(rssi-2);
  }
  else if(rssi > 30) {
    rssi = -51 + (rssi-30)/2;   // approximate
  }
  
  SerialUSB.print(rssi);
  SerialUSB.println("dBm");
  delay(1000);
}
