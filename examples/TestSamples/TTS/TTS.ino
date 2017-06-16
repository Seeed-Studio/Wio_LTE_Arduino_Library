#include "module_common.h"
#include "Arduino_Interface.h"


WioTracker wio = WioTracker();

void setup() {
  SerialUSB.begin(115200);
  // delay(5000);
  SerialUSB.println("Begin...");

  wio.Power_On();
  while(false == wio.Check_If_Power_On()){
    SerialUSB.println("Waitting for module to alvie...");
    delay(1000);
  }  
  SerialUSB.println("Power On O.K!");
}

void loop() {
  /* Debug */
  // if(SerialUSB.available()){
  //   MODULE_PORT.write(SerialUSB.read());
  // }
  // if(MODULE_PORT.available()){     
  //   SerialUSB.write(MODULE_PORT.read()); 
  // }

  bool ret;

  SerialUSB.println("Play TTS Test...");
  ret = check_with_cmd("AT+QTTS=1, \"6B228FCE4F7F752879FB8FDC6A215757\"\r\n", "OK", CMD, 2, 2000);
  delay(8000);

  ret = check_with_cmd("AT+QFLST\r\n", "test.wav", CMD, 2, 2000);
  if(ret){
    check_with_cmd("AT+QFDEL=\"test.wav\"\r\n", "OK", CMD, 2, 2000);
    SerialUSB.println("Delete record file.");
  } else{
    SerialUSB.println("Didn't find record file.");
  }


  
  ret = check_with_cmd("AT+QAUDRD=1,\"test.wav\"\r\n", "OK", CMD, 2, 2000);
  if(ret){
    SerialUSB.println("Start record...");
  }else{
    SerialUSB.println("Start record failed...");
  }
  delay(5000);

  
  ret = check_with_cmd("AT+QAUDRD=0\r\n", "OK", CMD, 2, 2000);
  if(ret){
    SerialUSB.println("Stop record...");
  } else{
    SerialUSB.println("Stop record failed...");
  }
  delay(1000);

  SerialUSB.println("Play record...");
  ret = check_with_cmd("AT+QAUDPLAY=\"test.wav\",0\r\n", "+QAUDPIND: 0,1", CMD, 2, 2000);
  if(ret){
    SerialUSB.println("Play failed...");
  }else {
    SerialUSB.println("Playing...");
    delay(5000);
  }



    SerialUSB.println("");
}
