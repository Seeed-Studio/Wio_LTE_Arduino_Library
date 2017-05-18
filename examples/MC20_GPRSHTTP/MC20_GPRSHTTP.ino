#include "MC20_Common.h"
#include "MC20_Arduino_Interface.h"
#include "MC20_GPRS.h"

#define RGBPIN 10

GPRS gprs = GPRS();
const char apn[10] = "CMNET";
// const char apn[10] = "UNINET";
const char URL[100] = "mbed.org";
char http_cmd[100] = "GET /media/uploads/mbed_official/hello.txt HTTP/1.0\n\r\n\r";
int port = 80;

int ret = 0;

void setup() {
  pinMode(RGBPIN, OUTPUT);
  digitalWrite(RGBPIN, LOW);
  SerialUSB.begin(115200);

  gprs.Power_On();
  SerialUSB.println("\n\rPower On!");

  if(!(ret = gprs.init(apn))) {
    SerialUSB.print("GPRS init error: ");
    SerialUSB.println(ret);
  }

  gprs.join();
  SerialUSB.print("\n\rIP: ");
  SerialUSB.print(gprs.ip_string);

  if(gprs.connectTCP(URL, port)) {
    gprs.sendTCPData(http_cmd);  
  } else {
    SerialUSB.println("Connect Error!");
  }
}

void loop() {
  /* Debug */
  if(SerialUSB.available()){
    serialMC20.write(SerialUSB.read());
  }
  if(serialMC20.available()){     
    SerialUSB.write(serialMC20.read()); 
  }

}
