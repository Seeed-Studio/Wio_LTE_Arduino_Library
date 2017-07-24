#include "module_common.h"
#include "Arduino_Interface.h"

#define RGBPIN 10

const char message[128] = "Hello MC20!";

WioTracker wio = WioTracker();

void setup() {
  wio.Power_On();
  SerialUSB.println("Power On!");

  if(!wio.waitForNetworkRegister())
  {
    SerialUSB.println("Network error!");
    return;
  } else {
    SerialUSB.println("Network ready!");
  }

  wio.sendSMS("13750024343", "Hello from Wio Traker!");  // Change ****** to your test phone number

}

void loop() {
  AT_bypass();
}
