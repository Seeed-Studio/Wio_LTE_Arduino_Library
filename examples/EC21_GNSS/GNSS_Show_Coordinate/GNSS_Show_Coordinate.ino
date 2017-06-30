#include "module_common.h"
#include "Arduino_Interface.h"
#include "gnss.h"


GNSS gnss = GNSS();

void setup() {
  // Enable Module Power
  pinMode(gnss.MODULE_PWR_PIN, OUTPUT);
  digitalWrite(gnss.MODULE_PWR_PIN , HIGH);    
  // Enable VCCB
  pinMode(gnss.ENABLE_VCCB_PIN, OUTPUT);
  digitalWrite(gnss.ENABLE_VCCB_PIN, HIGH);

  // Module power on
  gnss.Power_On();
  while(false == gnss.Check_If_Power_On()){
    SerialUSB.println("Waitting for module to alvie...");
    delay(1000);
  } 
  SerialUSB.println("\n\rPower On!");

  if(!(gnss.open_GNSS())){
    SerialUSB.println("\n\rGNSS init failed!");
    return;
  }

  SerialUSB.println("Open GNSS OK.");
  delay(2000);
}

void loop() {
  char buffer[64];
  if(gnss.getCoordinate()){
    SerialUSB.print("GNSS: ");
    SerialUSB.print(gnss.longitude, 6);
    SerialUSB.print(",");
    SerialUSB.println(gnss.latitude, 6);
    SerialUSB.print(gnss.str_longitude);
    SerialUSB.print(",");
    SerialUSB.println(gnss.str_latitude);
  } else{
    SerialUSB.println("Error!");
  }
  
  delay(1000);
}
