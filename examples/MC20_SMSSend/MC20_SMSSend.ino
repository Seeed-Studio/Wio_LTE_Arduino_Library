#include "MC20_Common.h"
#include "MC20_Arduino_Interface.h"

#define RGBPIN 10

const char message[128] = "Hello MC20!";

GPSTracker gpsTracker = GPSTracker();

void setup() {
  pinMode(RGBPIN, OUTPUT);
  digitalWrite(RGBPIN, LOW);
  SerialUSB.begin(115200);
  while(!SerialUSB);

  gpsTracker.Power_On();
  SerialUSB.println("Power On!");

  if(!gpsTracker.waitForNetworkRegister())
  {
    SerialUSB.println("Network error!");
    return;
  }

  gpsTracker.sendSMS("xxxxxxxxxxx", "Hello MC20!");  // Change ****** to your test phone number

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
