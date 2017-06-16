/*
 * gnss.cpp
 * A library for SeeedStudio GPS Tracker BT 
 *
 * Copyright (c) 2017 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : lawliet zou, lambor
 * Create Time: April 2017
 * Change Log :
 *
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "gnss.h"


// bool GNSS::initialize()
// {
//     return true;
// }

bool GNSS::close_GNSS()
{
  int errCounts = 0;

  //Open GNSS funtion
  while(!check_with_cmd("AT+QGNSSC?\n\r", "+QGNSSC: 0", CMD, 2, 2000, UART_DEBUG)){
      errCounts ++;
      if(errCounts > 100){
        return false;
      }
      check_with_cmd("AT+QGNSSC=0\n\r", "OK", CMD, 2, 2000, UART_DEBUG);
      delay(1000);
  }

  return true;
}

bool GNSS::dataFlowMode(void)
{
    // Make sure that "#define UART_DEBUG" is uncomment.
    send_cmd("AT+QGPSLOC?\n\r");
    return wait_for_resp("OK", CMD, 2, 2000, true);
    // return check_with_cmd("AT+QGNSSRD?\n\r", "OK", CMD);
}

// bool GNSS::open_GNSS(int mode)
// {
//   bool ret = true;

//   switch(mode){
//     case GNSS_DEFAULT_MODE:
//       ret = open_GNSS_default_mode();   // Default GNSS mode
//       break;
//     case EPO_QUICK_MODE:
//       ret = open_GNSS_EPO_quick_mode(); // Quick mode with EPO
//       break;
//     case EPO_LP_MODE:
//       ret = open_GNSS_EPO_LP_mode();   // Low power consumption mode with EPO
//       break;
//     case EPO_RL_MODE:
//       ret = open_GNSS_RL_mode();     // Reference-location mode
//       break;
//   };
  
//   return ret;
// }

bool GNSS::open_GNSS(void)
{
  int errCounts = 0;

  //Open GNSS funtion
  while(!check_with_cmd("AT+QGPS?\r\n", "+QGPS: 1", CMD, 2, 2000, UART_DEBUG)){
      errCounts ++;
      if(errCounts > 5){
        return false;
      }
      check_with_cmd("AT+QGPS=1\r\n", "OK", CMD, 2, 2000, UART_DEBUG);
      delay(1000);
  }

  return true;
}

// bool GNSS::open_GNSS_default_mode(void)
// {
//   return open_GNSS();
// }

// bool GNSS::open_GNSS_EPO_quick_mode(void)
// {
//   //Open GNSS funtion
//   if(!open_GNSS()){
//     return false;
//   }

//   //
//   if(!settingContext()){
//     return false;
//   }

//   // Check network register status
//   if(!isNetworkRegistered()){
//     return false;
//   }

//   // Check time synchronization status
//   if(!isTimeSynchronized()){
//     return true;  // Return true to work on 
//   }

//   // Enable EPO funciton
//   if(!enableEPO()){
//     return false;
//   }

//   // Trigger EPO funciton
//   if(!triggerEPO()){
//     return false;
//   }

//   return true;
// }
// bool GNSS::open_GNSS_EPO_LP_mode(void)
// {
//   //
//   if(!settingContext()){
//     return false;
//   }

//   // Check network register status
//   if(!isNetworkRegistered()){
//     return false;
//   }

//   // Check time synchronization status
//   if(!isTimeSynchronized()){
//     //Open GNSS funtion
//     if(!open_GNSS()){
//       return false;
//     }
//     return true;  // Return true to work on 
//   }

//   // Enable EPO funciton
//   if(!enableEPO()){
//     return false;
//   }

//   // Trigger EPO funciton
//   if(!triggerEPO()){
//     return false;
//   }

//   //Open GNSS funtion
//   if(!open_GNSS()){
//     return false;
//   }

//   return true;
// }

// bool GNSS::open_GNSS_RL_mode(void)
// {
//   int errCounts = 0;
//   char buffer[128];
//   clean_buffer(buffer, 128);

//   //
//   if(!settingContext()){
//     return false;
//   }

//   // Check network register status
//   if(!isNetworkRegistered()){
//     return false;
//   }

//   // Check time synchronization status
//   if(!isTimeSynchronized()){
//     //Open GNSS funtion
//     if(!open_GNSS()){
//       return false;
//     }
//     return true;  // Return true to work on 
//   }

//   // Write in reference-location
//   // sprintf(buffer, "AT+QGREFLOC=%f,%f\n\r", ref_longitude, ref_latitude);
//   sprintf(buffer, "AT+QGREFLOC=22.584322,113.966678\n\r\n\r");
//   if(!check_with_cmd("AT+QGREFLOC=22.584322,113.966678\n\r", "OK", CMD, 2, 2000, UART_DEBUG)){
//     errCounts++;
//     if(errCounts > 3)
//     {
//       return false;
//     }
//     delay(1000);
//   }

//   // Enable EPO funciton
//   if(!enableEPO()){
//     return false;
//   }

//   // Trigger EPO funciton
//   if(!triggerEPO()){
//     return false;
//   }

//   //Open GNSS funtion
//   if(!open_GNSS()){
//     return false;
//   }

//   return true;
// }

// void GNSS::doubleToString(double longitude, double latitude)
// {
//   int u8_lon = (int)longitude;
//   int u8_lat = (int)latitude;
//   uint32_t u32_lon = (longitude - u8_lon)*1000000;
//   uint32_t u32_lat = (latitude - u8_lat)*1000000;

//   sprintf(str_longitude, "%d.%lu", u8_lon, u32_lon);
//   sprintf(str_latitude, "%d.%lu", u8_lat, u32_lat);
// }

// bool GNSS::getCoordinate(void)
// {
//     int i = 0;
//     int j = 0;
//     int tmp = 0;
//     char *p = NULL;
//     char buffer[1024];
//     char strLine[128];
//     char *header = "$GNGGA,";

//     p = &header[0];

//     clean_buffer(buffer, 1024);
//     send_cmd("AT+QGNSSRD?\n\r");
//     read_buffer(buffer, 1024, 2);
//     // SerialUSB.println(buffer);
//     if(NULL != strstr("+CME ERROR:", buffer))
//     {
//       return false;
//     }
//     while(buffer[i] != '\0'){
//         if(buffer[i] ==  *(p+j)){
//             j++;
//             // SerialUSB.print(i);
//             // SerialUSB.println(buffer[i]);
//             if(j >= 7) {
//                 p = &buffer[i];
//                 i = 0;
//                 while(*(p++) != '\n'){
//                     // SerialUSB.write(*p);
//                     strLine[i++] = *p;
//                 }
//                 strLine[i] = '\0';
//                 //SerialUSB.println(strLine);  // 093359.000,2235.0189,N,11357.9816,E,2,17,0.80,35.6,M,-2.5,M,,*51
//                 p = strtok(strLine, ","); // time
//                 p = strtok(NULL, ",");  // latitude
//                 sprintf(str_latitude, "%s", p); 
//                 latitude = strtod(p, NULL);
//                 tmp = (int)(latitude / 100);
//                 latitude = (double)(tmp + (latitude - tmp*100)/60.0);

//                 // Get North and South status
//                 p = strtok(NULL, ",");  // North or South
//                 sprintf(North_or_South, "%s", p); 

//                 p = strtok(NULL, ",");  // longitude
//                 sprintf(str_longitude, "%s", p);
//                 longitude = strtod(p, NULL);

//                 // Get West and East status
//                 p = strtok(NULL, ",");  // West or East
//                 sprintf(West_or_East, "%s", p); 

//                 tmp = (int)(longitude / 100);
//                 longitude = (double)(tmp + (longitude - tmp*100)/60.0);

//                 // if(North_or_South[0] == 'S'){
//                 //     // latitude = 0.0 - latitude;
//                 // } else if(North_or_South[0] = 'N'){
//                 //     latitude = 0.0 - latitude;
//                 // }

//                 // if(West_or_East[0] == 'W'){
//                 //     // longitude = 0.0 - longitude;
//                 // } else if(West_or_East[0] = 'E'){
//                 //     longitude = 0.0 - longitude;
//                 // }

//                 doubleToString(longitude, latitude);
//                 break;
//             }
//         } else {
//             j = 0;
//         }
//         i++;
//     }

//     return true;
// }


// bool GNSS::settingContext(void)
// {
//   int errCounts = 0;

//   //Setting context
//   while(!check_with_cmd("AT+QIFGCNT=2\n\r", "OK", CMD, 2, 2000, UART_DEBUG)){
//     errCounts++;
//     if(errCounts > 3)
//     {
//       return false;
//     }
//     delay(1000);
//   }

//   return true;
// }

// bool GNSS::isNetworkRegistered(void)
// {
//   int errCounts = 0;

//   //
//   while(!check_with_cmd("AT+CREG?\n\r", "+CREG: 0,1", CMD, 2, 2000, UART_DEBUG)){
//     errCounts++;
//     if(errCounts > 30)    // Check for 30 times
//     {
//       return false;
//     }
//     delay(1000);
//   }

//   errCounts = 0;
//   while(!check_with_cmd("AT+CGREG?\n\r", "+CGREG: 0,1", CMD, 2, 2000, UART_DEBUG)){
//     errCounts++;
//     if(errCounts > 30)    // Check for 30 times
//     {
//       return false;
//     }
//     delay(1000);
//   }

//   return true;
// }

// bool GNSS::isTimeSynchronized(void)
// {
//   int errCounts = 0;

//   // Check time synchronization status
//   errCounts = 0;
//   while(!check_with_cmd("AT+QGNSSTS?\n\r", "+QGNSSTS: 1", CMD, 2, 2000, UART_DEBUG)){
//     errCounts++;
//     if(errCounts > 2)  // Check Time asynchronize 
//     {
//       return true;
//     }
//     delay(1000);
//   }  

//   return true;
// }

// bool GNSS::enableEPO(void)
// {
//   int errCounts = 0;

//   //
//   if(!check_with_cmd("AT+QGNSSEPO=1\n\r\n\r", "OK", CMD, 2, 2000, UART_DEBUG)){
//     errCounts++;
//     if(errCounts > 3)
//     {
//       return false;
//     }
//     delay(1000);
//   }
  
//   return true;
// }

// bool GNSS::triggerEPO(void)
// {
//   int errCounts = 0;

//   //
//   if(!check_with_cmd("AT+QGEPOAID\n\r", "OK", CMD, 2, 2000, UART_DEBUG)){
//     errCounts++;
//     if(errCounts > 3)
//     {
//       return false;
//     }
//     delay(1000);
//   }

//   return true;
// }

// uint8_t GNSS::getCheckSum(char *string)
// {
//   uint8_t XOR = 0;  
//   for (int i = 0; i < strlen(string); i++) 
//   {
//     XOR = XOR ^ string[i];
//   }
//   return (XOR/16)*10 + (XOR%16);
// }

// bool GNSS::enable_EASY(void)
// {
//   int errCounts = 0;

//   //
//   if(!check_with_cmd("AT+QGNSSCMD=0,\"$PMTK869,1,1*35\"\n\r", "OK", CMD, 2, 2000, UART_DEBUG)){
//     errCounts++;
//     if(errCounts > 3)
//     {
//       return false;
//     }
//     delay(1000);
//   }

//   return true;
// }


// bool GNSS::enable_GLP(int enable, int save)
// {
//   char str_buf[11];
//   char buf_w[64];
//   char checkSum;

//   clean_buffer(str_buf, 11);
//   sprintf(str_buf, "PQGLP,W,%d,%d", enable, save);
//   checkSum = getCheckSum(str_buf);

//   clean_buffer(buf_w, 64);
//   sprintf(buf_w, "AT+QGNSSCMD=0,\"$%s*%d\"", str_buf, checkSum);

//     //
//   send_cmd(buf_w);
//   if(!check_with_cmd("\n\r", "+QGNSSCMD: $PQGLP,W,OK*09", CMD, 5, 2000, UART_DEBUG)){
//     return false;
//   }

//   return true;
// }


// bool GNSS::eraseFlash_LOCUS(void)
// {
//   return check_with_cmd("AT+QGNSSCMD=0,\"$PMTK184,1*22\"\n\r", "+QGNSSCMD: $PMTK001,184,3*3D", CMD, 5, 2000, UART_DEBUG);
// }

// bool GNSS::stopLogger_LOCUS(int status)
// {
//   char str_buf[11];
//   char buf_w[64];
//   char checkSum;

//   clean_buffer(str_buf, 11);
//   sprintf(str_buf, "PMTK185,%d", status);
//   checkSum = getCheckSum(str_buf);

//   clean_buffer(buf_w, 64);
//   sprintf(buf_w, "AT+QGNSSCMD=0,\"$%s*%d\"", str_buf, checkSum);

//   //
//   send_cmd(buf_w);
//   if(!check_with_cmd("\n\r", "+QGNSSCMD: $PMTK001,185,3*3C", CMD, 5, 2000)){
//     return false;
//   }

//   return true;
// }

// bool GNSS::queryData_LOCUS(void)
// {
//   return check_with_cmd("AT+QGNSSCMD=0,\"$PMTK622,1*29\"\n\r", "+QGNSSCMD: $PMTK001,184,3*3D", CMD, 5, 2000, true);
// }

// bool GNSS::set1PPS(bool status)
// {
//   if(status){
//     return check_with_cmd("AT+QGNSSCMD=0,\"$PMTK255,1*2D\"\n\r", "+QGNSSCMD: $PMTK001,255,3*32", CMD, 5, 2000, true);
//   } else{
//     return check_with_cmd("AT+QGNSSCMD=0,\"$PMTK255,0*2C\"\n\r", "+QGNSSCMD: $PMTK001,255,3*32", CMD, 5, 2000, true);
//   }

//   return true;
// }

// bool GNSS::setAlwaysLocateMode(int mode)
// {
//   char str_buf[11];
//   char buf_w[64];
//   char checkSum;

//   clean_buffer(str_buf, 11);
//   sprintf(str_buf, "PMTK225,%d", mode);
//   checkSum = getCheckSum(str_buf);

//   clean_buffer(buf_w, 64);
//   sprintf(buf_w, "AT+QGNSSCMD=0,\"$%s*%d\"", str_buf, checkSum);

//   //
//   send_cmd(buf_w);
//   if(!check_with_cmd("\n\r", "+QGNSSCMD: $PMTK001,225,3*35", CMD, 5, 2000, true)){
//     return false;
//   }

//   return true;
// }

// bool GNSS::select_searching_satellite(int gps, int beidou)
// {
//   char str_buf[20];
//   char buf_w[64];
//   char checkSum;

//   clean_buffer(str_buf, 20);
//   sprintf(str_buf, "PMTK353,%d,0,0,0,%d", gps, beidou);
//   checkSum = getCheckSum(str_buf);

//   clean_buffer(buf_w, 64);
//   sprintf(buf_w, "AT+QGNSSCMD=0,\"$%s*%d\"", str_buf, checkSum);

//   send_cmd(buf_w);
//   if(gps == 0 && beidou == 1){
//     if(!check_with_cmd("\n\r", "+QGNSSCMD: $PMTK001,353,3,0,0,0,0,1,48*08", CMD, 5, 2000)){
//       return false;
//     }
//   } else {
//     if(!check_with_cmd("\n\r", "+QGNSSCMD: $PMTK001,262,3,0*2A", CMD, 5, 2000)){
//       return false;
//     }
//   }
  

//   return true;
// }

// bool GNSS::setWorkMode(int mode)
// {
//   char str_buf[11];
//   char buf_w[64];
//   char checkSum;

//   clean_buffer(str_buf, 11);
//   sprintf(str_buf, "PMTK225,%d", mode);
//   checkSum = getCheckSum(str_buf);

//   clean_buffer(buf_w, 64);
//   sprintf(buf_w, "AT+QGNSSCMD=0,\"$%s*%d\"", str_buf, checkSum);

//   //
//   send_cmd(buf_w);
//   if(!check_with_cmd("\n\r", "+QGNSSCMD: $PMTK001,225,3*35", CMD, 5, 2000)){
//     return false;
//   }

//   return true;
// }

// bool GNSS::setStandbyMode(int mode)
// {
//   char str_buf[11];
//   char buf_w[64];
//   char checkSum;
//   int errCount = 0;

//   clean_buffer(str_buf, 11);
//   sprintf(str_buf, "PMTK161,%d", mode);
//   checkSum = getCheckSum(str_buf);

//   clean_buffer(buf_w, 64);
//   sprintf(buf_w, "AT+QGNSSCMD=0,\"$%s*%d\"", str_buf, checkSum);

//   //
//   send_cmd(buf_w);
//   while(!check_with_cmd("\n\r", "+QGNSSCMD: $PMTK001,161,3*36", CMD, 5, 2000)){
//   // while(!check_with_cmd("\n\r", "OK", CMD, 5, 2000)){
//     errCount ++;
//     if(errCount > 10){
//       return false;
//     }
//     send_cmd(buf_w);
//     SerialUSB.println(__LINE__);
//     delay(1000);
//   }

//   return true;
// }
