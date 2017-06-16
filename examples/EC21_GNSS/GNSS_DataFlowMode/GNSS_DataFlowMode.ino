#include "module_common.h"
#include "Arduino_Interface.h"
#include "gnss.h"
#include "SeeedGrayOLED.h"
#include "Wire.h"

GNSS gnss = GNSS();
bool is_gnss_ok = false;
char buf[16];

void setup() {
  // Open VCCB
  pinMode(gnss.ENABLE_VCCB_PIN, OUTPUT);
  digitalWrite(gnss.ENABLE_VCCB_PIN, HIGH);

  SerialUSB.begin(115200);

  Wire.begin();
  SeeedGrayOled.init(SH1107G);             //initialize SEEED OLED display
  SeeedGrayOled.clearDisplay();     //Clear Display.
  SeeedGrayOled.setNormalDisplay(); //Set Normal Display Mode
  SeeedGrayOled.setVerticalMode();  // Set to vertical mode for displaying text
  SeeedGrayOled.setTextXY(0,0);  //set Cursor to ith line, 0th column
  SeeedGrayOled.putString("Hello World"); //Print Hello World


  gnss.Power_On();
  while(false == gnss.Check_If_Power_On()){
    SerialUSB.println("Waitting for module to alvie...");
    delay(1000);
  } 
  SerialUSB.println("\n\rPower On!");

  if(!(is_gnss_ok = gnss.open_GNSS())){
    SerialUSB.println("\n\rGNSS init failed!");
    return;
  }
  
  check_with_cmd("AT+QGPS=1\r\n", "OK", CMD, 2, 2000, UART_DEBUG);

  SerialUSB.println("Open GNSS OK.");
  delay(2000);

}

void loop() {
  clean_buffer(buf, 16);
  if(is_gnss_ok){
    gnss.dataFlowMode();
    // send_cmd("AT+QGPSLOC?\n\r");
    // read_buffer(buf, 16, 2, 2000);
    // flush_serial();
    // SeeedGrayOled.setTextXY(0,0);  //set Cursor to ith line, 0th column
    // SeeedGrayOled.putString(buf); //Print Hello World
  }
  delay(1000);  
}
