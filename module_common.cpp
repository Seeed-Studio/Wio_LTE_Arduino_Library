/*
 * module_common.cpp
 * A library for SeeedStudio GPS Tracker
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

 #include <stdio.h>
 #include "module_Common.h"

// WioTracker* WioTracker::inst;

WioTracker::WioTracker()
{
    // pinMode(PWR_KEY_PIN, OUTPUT);
    // pinMode(MODULE_PWR_PIN, OUTPUT);
    // pinMode(ENABLE_VCCB_PIN, OUTPUT);
    // pinMode(RESET_MODULE_PIN, OUTPUT);
    // pinMode(WAKEUP_IN_PIN, OUTPUT);
    // pinMode(STATUS_PIN, INPUT);

    // digitalWrite(PWR_KEY_PIN, HIGH);
    // digitalWrite(MODULE_PWR_PIN, HIGH);     // Module Power Default HIGH
    // digitalWrite(ENABLE_VCCB_PIN, LOW);    // VCC_B Enable pin
    // digitalWrite(RESET_MODULE_PIN, HIGH);  // RESET_N Default HIGH 

    // Module_init();
}

bool WioTracker::init(void)
{
    if(!check_with_cmd(F("AT\r\n"),"OK\r\n",CMD)){
        return false;
    }
    
    if(!check_with_cmd(F("AT+CPIN?\r\n"),"OK\r\n",CMD)){
        return false;
    }
    
    if(!checkSIMStatus()) {
        return false;
    }
    return true;
}

bool WioTracker::Check_If_Power_On(void)
{
  return check_with_cmd(F("AT\r\n"), "OK", CMD, 2, 2000, true);
}

void WioTracker::Power_On(void)
{
  int pwr_status = 1;
  int errCnt = 0;

  serialPort_init();

  if(Check_If_Power_On()){
    return;
  }    
  pinMode(MODULE_PWR_PIN, OUTPUT);
  pinMode(ENABLE_VCCB_PIN, OUTPUT);
  // pinMode(RESET_MODULE_PIN, OUTPUT);
  pinMode(WAKEUP_IN_PIN, OUTPUT);
  pinMode(STATUS_PIN, INPUT);

  // digitalWrite(PWR_KEY_PIN, HIGH);
  digitalWrite(MODULE_PWR_PIN, HIGH);     // Module Power Default HIGH
  digitalWrite(ENABLE_VCCB_PIN, HIGH);    // VCC_B Enable pin
  // digitalWrite(RESET_MODULE_PIN, HIGH);  // RESET_N Default HIGH 
  
  digitalWrite(MODULE_PWR_PIN, HIGH);
  digitalWrite(WAKEUP_IN_PIN, LOW);
  delay(500);
  pinMode(PWR_KEY_PIN, OUTPUT);
  digitalWrite(PWR_KEY_PIN, HIGH);
  SerialUSB.print("STATUS_PIN 1: ");
  SerialUSB.println(digitalRead(STATUS_PIN));
  digitalWrite(PWR_KEY_PIN, LOW);
  delay(2000);
  digitalWrite(PWR_KEY_PIN, HIGH);
  delay(500);

  while(pwr_status == 1){
    pwr_status = digitalRead(STATUS_PIN);
    SerialUSB.print("STATUS_PIN 2: ");
    SerialUSB.println(pwr_status);
    delay(1000);
    errCnt++;  
    if(errCnt > 5){
      SerialUSB.println("Power On Fail...");
      return;
    }
  }
}

void WioTracker::powerReset(void)
{ 
  
}
  
void WioTracker::io_init()
{
  for(int i = 0; i< 20; i++){
   pinMode(12, OUTPUT);
   digitalWrite(i, LOW);
  }
}
  
bool WioTracker::checkSIMStatus(void)
{
    char Buffer[32];
    int count = 0;
    clean_buffer(Buffer,32);
    while(count < 3) {
        send_cmd("AT+CPIN?\r\n");
        read_buffer(Buffer,32,DEFAULT_TIMEOUT);
        if((NULL != strstr(Buffer,"+CPIN: READY"))) {
            break;
        }
        count++;
        delay(300);
    }
    if(count == 3) {
        return false;
    }
    return true;
}

bool WioTracker::waitForNetworkRegister(void)
{
  int errCounts = 0;

  //
  while(!check_with_cmd("AT+CREG?\n\r", "+CREG: 0,1", CMD, 2, 2000)){
    errCounts++;
    if(errCounts > 30)    // Check for 30 times
    {
      return false;
    }
    delay(1000);
  }

  errCounts = 0;
  while(!check_with_cmd("AT+CGREG?\n\r", "+CGREG: 0,1", CMD, 2, 2000)){
    errCounts++;
    if(errCounts > 30)    // Check for 30 times
    {
      return false;
    }
    delay(1000);
  }

  return true;
}

bool WioTracker::sendSMS(char *number, char *data)
{
    //char cmd[32];
    if(!check_with_cmd(F("AT+CMGF=1\r\n"), "OK\r\n", CMD)) { // Set message mode to ASCII
        return false;
    }
    delay(500);
    flush_serial();
    send_cmd("AT+CMGS=\"");
    send_cmd(number);
    if(!check_with_cmd(F("\"\r\n"),">",CMD)) {
        return false;
    }
    delay(1000);
    send_cmd(data);
    delay(500);
    send_End_Mark();
    return wait_for_resp("OK\r\n", CMD, 10);
}

// bool WioTracker::readSMS(int messageIndex, char *message, int length, char *phone, char *datetime)  
// {
//   /* Response is like:
//   AT+CMGR=2
  
//   +CMGR: "REC READ","XXXXXXXXXXX","","14/10/09,17:30:17+08"
//   SMS text here
  
//   So we need (more or lees), 80 chars plus expected message length in buffer. CAUTION FREE MEMORY
//   */

//     int i = 0;
//     char Buffer[80 + length];
//     //char cmd[16];
//     char num[4];
//     char *p,*p2,*s;
    
//     check_with_cmd(F("AT+CMGF=1\r\n"),"OK\r\n",CMD);
//     delay(1000);
//     //sprintf(cmd,"AT+CMGR=%d\r\n",messageIndex);
//     //send_cmd(cmd);
//     send_cmd("AT+CMGR=");
//     itoa(messageIndex, num, 10);
//     send_cmd(num);
//     send_cmd("\r\n");
//     clean_buffer(Buffer,sizeof(Buffer));
//     read_buffer(Buffer,sizeof(Buffer));
      
//     if(NULL != ( s = strstr(Buffer,"READ\",\""))){
//         // Extract phone number string
//         p = strstr(s,",");
//         p2 = p + 2; //We are in the first phone number character
//         p = strstr((char *)(p2), "\"");
//         if (NULL != p) {
//             i = 0;
//             while (p2 < p) {
//                 phone[i++] = *(p2++);
//             }
//             phone[i] = '\0';            
//         }
//         // Extract date time string
//         p = strstr((char *)(p2),",");
//         p2 = p + 1; 
//         p = strstr((char *)(p2), ","); 
//         p2 = p + 2; //We are in the first date time character
//         p = strstr((char *)(p2), "\"");
//         if (NULL != p) {
//             i = 0;
//             while (p2 < p) {
//                 datetime[i++] = *(p2++);
//             }
//             datetime[i] = '\0';
//         }        
//         if(NULL != ( s = strstr(s,"\r\n"))){
//             i = 0;
//             p = s + 2;
//             while((*p != '\r')&&(i < length-1)) {
//                 message[i++] = *(p++);
//             }
//             message[i] = '\0';
//         }
//         return true;
//     }
//     return false;    
// }

// bool WioTracker::readSMS(int messageIndex, char *message,int length)
// {
//     int i = 0;
//     char Buffer[100];
//     //char cmd[16];
//     char num[4];
//     char *p,*s;
    
//     check_with_cmd(F("AT+CMGF=1\r\n"),"OK\r\n",CMD);
//     delay(1000);
//     send_cmd("AT+CMGR=");
//     itoa(messageIndex, num, 10);
//     send_cmd(num);
//     // send_cmd("\r\n");
//     send_cmd("\r\n");
// //  sprintf(cmd,"AT+CMGR=%d\r\n",messageIndex);
// //    send_cmd(cmd);
//     clean_buffer(Buffer,sizeof(Buffer));
//     read_buffer(Buffer,sizeof(Buffer),DEFAULT_TIMEOUT);
//     if(NULL != ( s = strstr(Buffer,"+CMGR:"))){
//         if(NULL != ( s = strstr(s,"\r\n"))){
//             p = s + 2;
//             while((*p != '\r')&&(i < length-1)) {
//                 message[i++] = *(p++);
//             }
//             message[i] = '\0';
//             return true;
//         }
//     }
//     return false;   
// }

// bool WioTracker::deleteSMS(int index)
// {
//     //char cmd[16];
//     char num[4];
//     //sprintf(cmd,"AT+CMGD=%d\r\n",index);
//     send_cmd("AT+CMGD=");
//     if(index > 998){
//         send_cmd("1,4");
//     }
//     else{
//         itoa(index, num, 10);
//         send_cmd(num);
//     }
//     // We have to wait OK response
//     //return check_with_cmd(cmd,"OK\r\n",CMD);
//     return check_with_cmd(F("\r"),"OK\r\n",CMD); 
// }


bool WioTracker::callUp(char *number)
{
    //char cmd[24];
    if(!check_with_cmd(F("AT+COLP=1\r\n"),"OK\r\n",CMD)) {
        return false;
    }
    delay(1000);
    //HACERR quitar SPRINTF para ahorar memoria ???
    //sprintf(cmd,"ATD%s;\r\n", number);
    //send_cmd(cmd);
    send_cmd("ATD");
    send_cmd(number);
    send_cmd(";\r\n");
    return true;
}

void WioTracker::answer(void)
{
    send_cmd("ATA\r\n");  //TO CHECK: ATA doesnt return "OK" ????
}

bool WioTracker::hangup(void)
{
    return check_with_cmd(F("ATH\r\n"),"OK\r\n",CMD);
}


bool WioTracker::getSignalStrength(int *buffer)
{
    //AT+CSQ                        --> 6 + CR = 10
    //+CSQ: <rssi>,<ber>            --> CRLF + 5 + CRLF = 9                     
    //OK                            --> CRLF + 2 + CRLF =  6

    byte i = 0;
    char Buffer[26];
    char *p, *s;
    char buffers[4];
    flush_serial();
    send_cmd("AT+CSQ\r");
    clean_buffer(Buffer, 26);
    read_buffer(Buffer, 26, DEFAULT_TIMEOUT);
    if (NULL != (s = strstr(Buffer, "+CSQ:"))) {
        s = strstr((char *)(s), " ");
        s = s + 1;  //We are in the first phone number character 
        p = strstr((char *)(s), ","); //p is last character """
        if (NULL != s) {
            i = 0;
            while (s < p) {
                buffers[i++] = *(s++);
            }
            buffers[i] = '\0';
        }
        *buffer = atoi(buffers);
        return true;
    }
    return false;
}

int WioTracker::recv(char* buf, int len)
{
    clean_buffer(buf,len);
    read_buffer(buf,len);   //Ya he llamado a la funcion con la longitud del buffer - 1 y luego le estoy añadiendo el 0
    return strlen(buf);
}

bool WioTracker::GSM_work_mode(int mode)
{
  char buf_w[20];
  clean_buffer(buf_w, 20);
  sprintf(buf_w, "AT+CFUN=%d", mode);
  send_cmd(buf_w);
  return check_with_cmd("\n\r", "OK", CMD, 2, 2000, UART_DEBUG);
}

bool WioTracker::GSM_config_slow_clk(int mode)
{
  char buf_w[20];
  clean_buffer(buf_w, 20);
  sprintf(buf_w, "AT+QSCLK=%d", mode);
  send_cmd(buf_w);
  return check_with_cmd("\n\r", "OK", CMD, 2, 2000, UART_DEBUG);
}

bool WioTracker::AT_PowerDown(void)
{
  return check_with_cmd("AT+QPOWD=1\n\r", "NORMAL POWER DOWN", CMD, 5, 2000, UART_DEBUG);
}

