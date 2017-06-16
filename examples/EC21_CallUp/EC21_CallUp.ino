#include "MC20_Common.h"

#define RGBPIN 10

GPSTracker gpsTracker = GPSTracker();


void setup() {
  // MC20_init();
  pinMode(RGBPIN, OUTPUT);
  digitalWrite(RGBPIN, LOW);
  SerialUSB.begin(115200);

  gpsTracker.Power_On();
  SerialUSB.println("Power On!");

  while(!gpsTracker.init()){
    delay(1000);
    SerialUSB.println("Accessing network...");
  }
  SerialUSB.println("Initialize done...");

  bool ret = gpsTracker.waitForNetworkRegister();
  if(true == ret){
      SerialUSB.println("Network accessed!");
  }else {
      SerialUSB.println("Network failed!");
      return;
  }

  // Make a phone call
  gpsTracker.callUp("xxxxxxxxxxx");
  SerialUSB.println("Calling...");

}

void loop() {
/* Debug */
  if(SerialUSB.available()){
    serialMC20.write(SerialUSB.read());
  }
  if(serialMC20.available()){
    SerialUSB.write(serialMC20.read());
  }

}
