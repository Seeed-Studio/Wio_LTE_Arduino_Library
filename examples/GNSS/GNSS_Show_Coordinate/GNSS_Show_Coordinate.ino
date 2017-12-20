#include "gnss.h"


GNSS gnss = GNSS();

void setup() {
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
  if(gnss.getCoordinate()){
    SerialUSB.print("GNSS: \r\n");

    // Output double type
    SerialUSB.print(gnss.longitude, 6);
    SerialUSB.print(",");
    SerialUSB.println(gnss.latitude, 6);
    
    // Output char* type
    SerialUSB.print(gnss.str_longitude);
    SerialUSB.print(",");
    SerialUSB.println(gnss.str_latitude);
    SerialUSB.println();
  } else{
    SerialUSB.println("Error!");
  }
  
  delay(1000);
}
