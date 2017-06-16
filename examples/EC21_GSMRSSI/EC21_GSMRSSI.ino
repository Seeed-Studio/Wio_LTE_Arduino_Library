#include "MC20_Common.h"
// #include <TimerTCC0.h>

GPSTracker gpsTracker = GPSTracker();

void setup() {
  SerialUSB.begin(115200);
  // while(!SerialUSB);

  gpsTracker.Power_On();
  SerialUSB.println("Power On!");

  // TimerTcc0.initialize(1000000);
  // TimerTcc0.attachInterrupt(timerIsr);

}
void loop() {
  int rssi;
  gpsTracker.getSignalStrength(&rssi);
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
