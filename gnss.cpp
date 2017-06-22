/*
 * gnss.cpp
 * A library for SeeedStudio GPS Tracker LTE GNSS
 *
 * Copyright (c) 2017 seeed technology inc.
 * Website    : www.seeed.cc
 * Author     : lambor
 * Create Time: June 2017
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
    send_cmd("AT+QGPSLOC?\r\n");
    return wait_for_resp("OK", CMD, 2, 2000, true);
}

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

