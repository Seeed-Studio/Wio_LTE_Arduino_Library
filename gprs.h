/*
 * gprs.h
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

#ifndef __GPRS_H__
#define __GPRS_H__

#include "module_common.h"
#include "Arduino_Interface.h"


// enum Protocol {
//     CLOSED = 0,
//     TCP    = 1,
//     UDP    = 2
// };

class GPRS : public WioTracker
{
public:
    uint32_t _ip;
    char ip_string[32];

    /** Create GPRS instance
     *  @param number default phone number during mobile communication
     */
    // GPRS();

    /** initialize GPRS module including SIM card check & signal strength
     *  @returns
     *      0 on success
     *      -1 on error
     */
    bool init(const char *apn);

    /** Join APN
     *  @return
     *        true Jion APN successfully
     *        false failed to join VPN
     */
    bool join();


    /** parse IP string
     *  @return
     *      ip in hex
     */
    uint32_t str_to_ip(const char* str);

    /** Recover Ip address
     *  @return
     *       IP string
     */
    char* recoverIPAddress();

    /** check network is OK or not
     *  @returns
     *      0 on success
     *      -1 on error
     */
    int networkCheck(void);

    /** build TCP connect
     *  @param  ip  ip address which will connect to
     *  @param  port    TCP server' port number
     *  @returns
     *      0 on success
     *      -1 on error
     */
    bool connectTCP(const char* ip, int port);

    /** send data to TCP server
     *  @param  data    data that will be send to TCP server
     *  @returns
     *      0 on success
     *      -1 on error
     */
    bool sendTCPData(char* data);

    /** close TCP connection
     *  @returns
     *      0 on success
     *      -1 on error
     */
    bool closeTCP(void);
};

#endif
