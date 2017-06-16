#include "Arduino.h"
#include "module_common.h"
#include "Arduino_Interface.h"
#include "pwr.h"

// Function declare
void mcu_standby();


WioTracker wio = WioTracker();


void setup() {
  SerialUSB.begin(115200);
  // delay(5000);
  SerialUSB.println("Begin...");

  // wio.Power_On();
  // while(false == wio.Check_If_Power_On()){
  //   SerialUSB.println("Waitting for module to alvie...");
  //   delay(1000);
  // }  
  // SerialUSB.println("Power On O.K!");
  pwr_init();
  hal_pwr_enter_sleep_mode();
  
}

void loop() {
  // /* Debug */
  // if(SerialUSB.available()){
  //   MODULE_PORT.write(SerialUSB.read());
  // }
  // if(MODULE_PORT.available()){     
  //   SerialUSB.write(MODULE_PORT.read()); 
  // }
  SerialUSB.println("MCU Standby Test!");
  delay(1000);
}



















