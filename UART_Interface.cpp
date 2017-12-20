/*
 * UART_Interface.cpp
 * A library for Arduino UART Interface
 *
 * Copyright (c) 2017 Seeed Technology Co., Ltd.
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

#include "UART_Interface.h"


void  serialPort_init()
{
    MODULE_PORT.begin(115200);
}

void AT_bypass()
{
    while(MODULE_PORT.available()){
        serialDebug.write(MODULE_PORT.read());
    }
    while(SerialUSB.available()){
        MODULE_PORT.write(SerialUSB.read());
    }
}

int check_readable()
{
    return MODULE_PORT.available();
}

int wait_readable (int wait_time)
{
    unsigned long timerStart;
    int dataLen = 0;
    timerStart = millis();
    while((unsigned long) (millis() - timerStart) > wait_time * 1000UL) {
        delay(500);
        dataLen = check_readable();
        if(dataLen > 0){
            break;
        }
    }
    return dataLen;
}

void flush_serial()
{
    while(check_readable()){
        MODULE_PORT.read();
    }
}

void read_buffer(char *buffer, int count, unsigned int timeout, unsigned int chartimeout)
{
    int i = 0;
    bool is_timeout = false;
    unsigned long timerStart, prevChar;
    timerStart = millis();
    prevChar = 0;
    while(1) {
        while (check_readable()) {
            char c = MODULE_PORT.read();
            prevChar = millis();
            buffer[i++] = c;
            if(i >= count)break;
        }
        if(i >= count)break;
        if ((unsigned long) (millis() - timerStart) > timeout * 1000UL) {
            break;
        }
        //If interchar Timeout => return FALSE. So we can return sooner from this function. Not DO it if we dont recieve at least one char (prevChar <> 0)
        if (((unsigned long) (millis() - prevChar) > chartimeout) && (prevChar != 0)) {
            break;
        }
    }
}

void clean_buffer(char *buffer, int count)
{
    for(int i=0; i < count; i++) {
        buffer[i] = '\0';
    }
}

//HACERR quitar esta funcion ?
void send_byte(uint8_t data)
{
    MODULE_PORT.write(data);
}

void send_char(const char c)
{
    MODULE_PORT.write(c);
}

void send_cmd(const char* cmd)
{
  for(uint16_t i=0; i<strlen(cmd); i++)
    {
        send_byte(cmd[i]);
    }
}

void send_cmd(const __FlashStringHelper* cmd)
{
  int i = 0;
  const char *ptr = (const char *) cmd;
  while (pgm_read_byte(ptr + i) != 0x00) {
    send_byte(pgm_read_byte(ptr + i++));
  }
}

void send_cmd_P(const char* cmd)
{
  while (pgm_read_byte(cmd) != 0x00)
    send_byte(pgm_read_byte(cmd++));
}

boolean Test_AT(void)
{
    return check_with_cmd("AT\r\n","OK",CMD);
}

void send_End_Mark(void)
{
    send_byte((char)26);
}

boolean wait_for_resp(const char* resp, DataType type, unsigned int timeout, unsigned int chartimeout, bool debug)
{
    int len = strlen(resp);
    int sum = 0;
    unsigned long timerStart, prevChar;    //prevChar is the time when the previous Char has been read.
    timerStart = millis();
    prevChar = 0;
    while(1) {
        if(check_readable()) {
            char c = MODULE_PORT.read();
            
            if(debug){
                DEBUG_BYTE(c);
            }

            prevChar = millis();
            sum = (c==resp[sum]) ? sum+1 : 0;
            if(sum == len)break;
        }
        if ((unsigned long) (millis() - timerStart) > timeout * 1000UL) {
            return false;
        }
        //If interchar Timeout => return FALSE. So we can return sooner from this function.
        if (((unsigned long) (millis() - prevChar) > chartimeout) && (prevChar != 0)) {
            return false;
        }

    }
    #ifdef UART_DEBUG
    serialDebug.println();
    #endif
    //If is a CMD, we will finish to read buffer.
    if(type == CMD) flush_serial();
    return true;
}


boolean check_with_cmd(const char* cmd, const char *resp, DataType type, unsigned int timeout, unsigned int chartimeout, bool debug)
{
    send_cmd(cmd);
    return wait_for_resp(resp,type,timeout,chartimeout,debug);
}

//HACERR que tambien la respuesta pueda ser FLASH STRING
boolean check_with_cmd(const __FlashStringHelper* cmd, const char *resp, DataType type, unsigned int timeout, unsigned int chartimeout, bool debug)
{
    send_cmd(cmd);
    return wait_for_resp(resp,type,timeout,chartimeout,debug);
}
