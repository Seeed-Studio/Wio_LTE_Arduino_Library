#include "MC20_Common.h"
#include "MC20_Arduino_Interface.h"
#include "MC20_GNSS.h"
#include <SeeedOLED.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

const int chipSelect = 4;
File myFile;
char* gpsFileName = "gps.txt";

GNSS gnss = GNSS();
bool gnss_sta;
long searching_gps_cnt = 0;
 
void setup() {
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  SerialUSB.begin(115200);
  // while(!SerialUSB);

  gnss.Power_On();
  SerialUSB.println("\n\rPower On!");

  while(!(gnss_sta = gnss.open_GNSS(GNSS_DEFAULT_MODE))){
    delay(1000);
  }

  SerialUSB.println("Open GNSS OK.");

  Wire.begin();
  SeeedOled.init();  //initialze SEEED OLED display

  SeeedOled.clearDisplay();          //clear the screen and set start position to top left corner
  SeeedOled.setNormalDisplay();      //Set display to normal mode (i.e non-inverse mode)
  SeeedOled.setPageMode();           //Set addressing mode to Page Mode

  if(gnss_sta){
    SeeedOled.setTextXY(1,0);          //Set the cursor to Xth Page, Yth Column  
    SeeedOled.putString("GNSS init OK"); //Print the String  
  }else{
    SeeedOled.setTextXY(1,0);          //Set the cursor to Xth Page, Yth Column  
    SeeedOled.putString("GNSS init failed"); //Print the String
  }
  
  
  if (!SD.begin(4)) {
    SerialUSB.println("initialization failed!");
    SeeedOled.setTextXY(0,0);          //Set the cursor to Xth Page, Yth Column  
    SeeedOled.putString("SD init failed!"); //Print the String
    return;
  }

  // createNewFile("gps.txt");
  if(SD.exists(gpsFileName)){
    SD.remove(gpsFileName);
  }

  SerialUSB.println("SD card initialization done.");
  SeeedOled.setTextXY(0,0);          //Set the cursor to Xth Page, Yth Column  
  SeeedOled.putString("SD initialOK!"); //Print the String
  SeeedOled.clearDisplay();          //clear the screen and set start position to top left corner
  delay(3000);
}

void loop() {

  if(!gnss.getCoordinate()){
    SerialUSB.println("Get GNSS Error!");
    SeeedOled.setTextXY(0,0);          //Set the cursor to Xth Page, Yth Column  
    SeeedOled.putString("Get GNSS Error!"); //Print the String
  }
  else if(gnss.longitude == 0 && gnss.latitude == 0){
    searching_gps_cnt++;
    SeeedOled.setTextXY(0,0);          //Set the cursor to Xth Page, Yth Column  
    SeeedOled.putString("Seaerching GPS."); //Print the String
    SeeedOled.setTextXY(1,0);          //Set the cursor to Xth Page, Yth Column 
    SeeedOled.putString("            "); //Print the String
    SeeedOled.setTextXY(1,0);          //Set the cursor to Xth Page, Yth Column 
    SeeedOled.putNumber(searching_gps_cnt); //Print the String
  }
  else{
    searching_gps_cnt = 0;
    SerialUSB.print("GNSS: ");
    SerialUSB.print(gnss.longitude, 6); 
    SerialUSB.print(",");
    SerialUSB.println(gnss.latitude, 6);

    
    myFile = SD.open(gpsFileName, FILE_WRITE);
    if(myFile){
      SerialUSB.println("Write file...");
      myFile.print(gnss.longitude, 6);
      myFile.print(", ");
      myFile.print(gnss.latitude, 6);
      myFile.println(", 0");
    }
    myFile.close();
    
    SeeedOled.clearDisplay();
    SeeedOled.setTextXY(0,0);          //Set the cursor to Xth Page, Yth Column  
    SeeedOled.putFloat(gnss.longitude, 6); //Print the String
    SeeedOled.setTextXY(2,0);          //Set the cursor to Xth Page, Yth Column  
    SeeedOled.putFloat(gnss.latitude, 6); //Print the String
  }

  delay(2000);
}