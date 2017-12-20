#include "gnss.h"

// Instance of GNSS class
GNSS gnss = GNSS();

void setup(){	
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

void loop(){
  char buffer[128];
  
  send_cmd("AT+QGPSLOC?\r\n");
  read_buffer(buffer, 128, 2, 2000);  
  SerialUSB.println(buffer);

  delay(2000);
}
