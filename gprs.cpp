/*
 * gprs.cpp
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

#include "gprs.h"

// bool GPRS::init(const char *apn)
// {
//     bool ret = false;
//     uint32_t timeStart = 0;

//     char sendBuffer[32];
//     clean_buffer(sendBuffer,32);
    
//     timeStart = millis();
//     while(!(ret = Test_AT())){
//         if((millis() - timeStart) > 10000){
//             return false;
//         }
//         delay(500);
//     }

//     // Config baudrate
//     if(!check_with_cmd("AT+IPR=115200&W\n\r", "OK", CMD)){
//         return false;
//     }
    
//     //AT+QIFGCNT=0 
//     if(!check_with_cmd("AT+QIFGCNT=0\n\r", "OK", CMD, DEFAULT_TIMEOUT)){
//         return false;
//     }

//     // Setting APN, AT+QICSGP=1,APN
//     clean_buffer(sendBuffer,32);
//     sprintf(sendBuffer, "AT+QICSGP=1,\"%s\"\n\r", apn);
//     if(!check_with_cmd(sendBuffer, "OK", CMD, DEFAULT_TIMEOUT)){
//         return false;
//     }

//     // Enter domain access
//     check_with_cmd("AT+QIDNSIP=1\n\r", "OK", CMD, 2);



//     return true;
// }

// bool GPRS::join(void)
// {
//     char *p;
//     int i = 0;
//     char ipAddr[32];
//     char sendBuffer[32];
//     int errCount = 0;
//     uint32_t timeStart = 0;

//     clean_buffer(ipAddr,32);
//     clean_buffer(sendBuffer,32);
   
//     //Select multiple connection
//     //check_with_cmd("AT+CIPMUX=1\r\n","OK",DEFAULT_TIMEOUT,CMD);

//     //AT+CPIN? 
//     timeStart = millis();
//     while(!check_with_cmd("AT+CPIN?\n\r","+CPIN: READY", CMD, 1)){
//         if(millis() - timeStart > 10000){
//             return false;
//         }
//         delay(1000);
//     }


//     //AT+CREG?
//     timeStart = millis();
//     while(!check_with_cmd("AT+CREG?\n\r","+CREG: 0,1", CMD, 1)){
//         if((millis() - timeStart) > 30000) {
//             return false;
//         }
//         delay(1000);
//     } 


//     timeStart = millis();
//     while(!check_with_cmd("AT+CGREG?\n\r","+CGREG: 0,1", CMD, 1)){
//         if((millis() - timeStart) > 30000) {
//             return false;
//         }
//         delay(1000);
//     }


//     timeStart = millis();
//     if(!check_with_cmd("AT+CGATT?\n\r","+CGATT: 1", CMD, 1)){
//         if((millis() - timeStart) > 30000) {
//             return false;
//         }
//         delay(1000);
//     }


// //=============================   Bellow three commands must be in sequence  ============================
//     // AT+QIREGAPP
//     timeStart = millis();
//     if(!check_with_cmd("AT+QIREGAPP\n\r", "OK", CMD, 1)){
//         powerReset();
//     }

//     // AT+QIACT
//     while(!check_with_cmd("AT+QIACT\n\r", "OK", CMD, 10)) {
//         if(errCount > 3){  // Times of error equals 3, reset power
//             powerReset();
//             return false;
//         }
//         errCount++;
//         delay(1000);
//     }

//     // Get IP address, AT+QILOCIP
//     clean_buffer(ipAddr, 32);
//     send_cmd("AT+QILOCIP\n\r");
//     read_buffer(ipAddr, 32);
//     errCount = 0;
//     while(NULL != strstr(ipAddr,"ERROR")) {
//         send_cmd("AT+QILOCIP\n\r");
//         read_buffer(ipAddr, 32);
//         if(errCount > 5){
//             return false;
//         }
//         errCount++;
        
//     }

//     p = &ipAddr[12];

//     while(*(p+i) != '\0'){
//         ip_string[i] = *(p+i);
//         i++;
//     }

//     ip_string[i] = '\0';
//     _ip = str_to_ip(p);
//     if(_ip != 0) {
//         return true;
//     }
// //========================================================================================================
//     return false;
// }

// uint32_t GPRS::str_to_ip(const char* str)
// {
//     uint32_t ip = 0;
//     char *p = (char*)str;
    
//     for(int i = 0; i < 4; i++) {
//         ip |= atoi(p);
//         p = strchr(p, '.');
//         if (p == NULL) {
//             break;
//         }
//         if(i < 3) ip <<= 8;
//         p++;
//     }
//     return ip;
// }

// //HACERR lo de la IP gasta muuuucho espacio (ver .h y todo esto)
// char* GPRS::recoverIPAddress()
// {
//     uint8_t a = (_ip>>24)&0xff;
//     uint8_t b = (_ip>>16)&0xff;
//     uint8_t c = (_ip>>8)&0xff;
//     uint8_t d = _ip&0xff;

//     snprintf(ip_string, sizeof(ip_string), "%d.%d.%d.%d", a,b,c,d);
//     return ip_string;
// }

// int GPRS::networkCheck(void)
// {
//     delay(1000);
//     if(0 != check_with_cmd("AT+CREG?\r\n","+CREG: 0,1",CMD, DEFAULT_TIMEOUT*3)) {
//         ERROR("ERROR:CGREG");
//         return -1;
//     }
//     delay(1000);
//     if(0 != check_with_cmd("AT+CGATT?\r\n","+CGATT: 1",CMD, DEFAULT_TIMEOUT)) {
//         ERROR("ERROR:CGATT");
//         return -1;
//     }
//     return 0;
// }

// bool GPRS::connectTCP(const char *ip, int port)
// {
//     uint8_t errCount = 0;
//     char cipstart[50];

//     sprintf(cipstart, "AT+QIOPEN=\"TCP\",\"%s\",%d\r\n", ip, port);
//     while(!check_with_cmd(cipstart, "CONNECT OK", CMD, 2*DEFAULT_TIMEOUT)) {// connect tcp
//         ERROR("ERROR:QIOPEN");
//         if(errCount > 3){
//             return false;
//         }
//         errCount++;
//     }

//     return true;
// }
// bool GPRS::sendTCPData(char *data)
// {
//     char cmd[32];
//     int len = strlen(data); 
//     snprintf(cmd,sizeof(cmd),"AT+QISEND=%d\r\n",len);
//     if(!check_with_cmd(cmd,">", CMD, 2*DEFAULT_TIMEOUT)) {
//         ERROR("ERROR:QISEND");
//         return false;
//     }
        
//     if(!check_with_cmd(data,"SEND OK", DATA, 2*DEFAULT_TIMEOUT)) {
//         ERROR("ERROR:SendTCPData");
//         return false;
//     }   
//     return true;
// }

// bool GPRS::closeTCP(void)
// {
//     send_cmd("AT+QICLOSE\r\n");
//     return true;
// }

