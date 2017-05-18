/********************************************************************************************
 This sketch demonstrates how sleep function using external interrupt to wake up the MCU.
 This sketch work only cortex-m0+ boards.
*********************************************************************************************/



#include <EnergySaving.h>
#include <Adafruit_NeoPixel.h>
#include "MC20_Common.h"
#include "MC20_Arduino_Interface.h"
#include "MC20_GNSS.h"


/**
 * Low Power mode setting
 */

#define MCU_SLEEP_AT_START
// #define GNSS_STANDBY
// #define GNSS_BACKUP
// #define GSM_SLEEP
// #define GSM_NORMAL_POWER_DOWN
#define GSM_WORK_MODE  0  // 0 - 最少功能， 1 - 全功能， 4 - 关闭RF

/*--------------------*/
/*--------------------*/

#define RGB_PIN    10
#define NUMPIXELS  1

#define DTR_PIN 9

int delayval = 500;

GNSS gnss = GNSS();

EnergySaving nrgSave;

unsigned int i=0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, RGB_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
 for(int i = 0; i< 20; i++){
   pinMode(i, OUTPUT);
   digitalWrite(i, LOW);
 }

#ifdef GNSS_BACKUP
  digitalWrite(12, HIGH);
#endif


//  digitalWrite(12, LOW);
//  digitalWrite(13, LOW);
//  digitalWrite(7, LOW);
//  digitalWrite(10, LOW);
  
  SerialUSB.begin(115200);

#ifdef MCU_SLEEP_AT_START
  nrgSave.begin(WAKE_EXT_INTERRUPT, 3, dummy);  //standby setup for external interrupts
  delay(4000);
  SerialUSB.println("MCU Stanby...");
  /*******************************************/
  // Add by JY.W 2017-04-22 20:57
  delay(1000);
  Serial1.end(); // Disable Uart
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  digitalWrite(0, LOW); // Rx
  digitalWrite(1, LOW); // Tx
  digitalWrite(9, LOW); // DTR  90uA
  /*******************************************/
  nrgSave.standby();  //now mcu goes in standby mode
#endif

  pinMode(DTR_PIN, OUTPUT);
  digitalWrite(DTR_PIN, HIGH);
  
  gnss.Power_On();
  SerialUSB.println("\n\rPower On!");

  if(!gnss.open_GNSS(GNSS_DEFAULT_MODE)){
    return;
  }

  delay(2000);

  // pixels.begin();
  nrgSave.begin(WAKE_EXT_INTERRUPT, 3, dummy);  //standby setup for external interrupts
}

void loop()
{
  bool ret; 


  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,4,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }

  delay(2000);
  
  for(int i=0;i<NUMPIXELS;i++){

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,0,0)); // Moderately bright green color.

    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }

#ifdef GNSS_STANDBY
  ret = gnss.setStandbyMode(0);
  SerialUSB.print("GNSS Stanby: ");
  SerialUSB.println(ret, DEC);
  delay(2000);
#endif

#ifdef GNSS_BACKUP
  /* 命令加引脚 */
  /*
  ret = gnss.close_GNSS();
  SerialUSB.print("GNSS backup mode: ");
  SerialUSB.println(ret, DEC);
  digitalWrite(12, LOW); // Disable GPS power
  */


  /* 命令 */
  ret = gnss.close_GNSS();
  SerialUSB.print("GNSS backup mode: ");
  SerialUSB.println(ret, DEC);
#endif

#ifdef GSM_SLEEP   // 进入 GSM sleep 模式， 先最少功能， 再sleep
  // 1.GSM function
  SerialUSB.println("GSM function...");
  ret = gnss.GSM_work_mode(GSM_WORK_MODE); 
  SerialUSB.print("GSM work mode: ");
  SerialUSB.print(GSM_WORK_MODE);
  SerialUSB.print(", Accessing status: ");
  SerialUSB.println(ret, DEC);
  delay(5000);
  
  // 2.GSM sleep Mode
  gnss.GSM_config_slow_clk(1);  // sleep mode
  digitalWrite(DTR_PIN, HIGH);  
  SerialUSB.println("GSM Sleep Mode ...");
#endif

#ifdef GSM_NORMAL_POWER_DOWN
  ret = gnss.AT_PowerDown();
  //digitalWrite(7, LOW);  // Shut down VBAT
  SerialUSB.print("GSM power down: ");
  SerialUSB.println(ret);
  delay(1000);
#endif

  digitalWrite(7, LOW);  // VBAT shut down

  /*******************************************/
  // Add by JY.W 2017-04-22 20:57
  delay(1000);
  Serial1.end(); // Disable Uart
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);
  digitalWrite(0, LOW); // Rx
  digitalWrite(1, LOW); // Tx
  digitalWrite(9, LOW); // DTR  90uA
  /*******************************************/
  
  
  SerialUSB.println("MCU Stanby...");
  nrgSave.standby();  //now mcu goes in standby mode
}


void dummy(void)  //interrupt routine (isn't necessary to execute any tasks in this routine
{
  
}
