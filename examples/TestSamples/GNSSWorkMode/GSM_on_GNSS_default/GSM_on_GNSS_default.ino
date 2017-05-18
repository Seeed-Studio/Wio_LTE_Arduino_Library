
#include "MC20_Common.h"
#include "MC20_Arduino_Interface.h"
#include "MC20_GNSS.h"

#define OPEN_GNSS
#define GSM_WORK_MODE  1  // 0 - 最少功能， 1 - 全功能， 4 - 关闭RF

GNSS gnss = GNSS();

void setup()
{
  // for(int i = 0; i< 20; i++){
  //   pinMode(i, OUTPUT);
  //   digitalWrite(i, LOW);
  // }
  
  SerialUSB.begin(115200);

  pinMode(gnss.DTR_PIN, OUTPUT);
  digitalWrite(gnss.DTR_PIN, HIGH);
  
  gnss.Power_On();
  SerialUSB.println("\n\rPower On!");

#ifdef OPEN_GNSS
  if(!gnss.open_GNSS(GNSS_DEFAULT_MODE)){
    return;
  }
#endif

  while(!gnss.waitForNetworkRegister()){
    delay(1000);
    SerialUSB.println("Wait for network...");
  }

  delay(2000);
}

void loop()
{
  bool ret; 

  // 1.GSM function
  SerialUSB.println("GSM function...");
  ret = gnss.GSM_work_mode(GSM_WORK_MODE); 
  SerialUSB.print("GSM work mode: ");
  SerialUSB.print(GSM_WORK_MODE);
  SerialUSB.print(", Accessing status: ");
  SerialUSB.println(ret, DEC);
  delay(5000); 


  while(1){
#ifdef OPEN_GNSS    
    gnss.dataFlowMode();
    delay(1000);
#endif      
  }
}


void dummy(void)  //interrupt routine (isn't necessary to execute any tasks in this routine
{
  
}
