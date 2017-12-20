#include "wio_tracker.h"

char message[128] = "Hello from Wio Traker!";

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
  
  // Change xxxxxxxxxxx to your test phone number
  if(wio.sendSMS("13750024343", message))
  {
    SerialUSB.println("Send OK!");
  }
  else 
  {
    SerialUSB.println("Send Error!");
  }

}

void loop() {
  AT_bypass();
}