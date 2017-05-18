#include "MC20_Common.h"
#include "MC20_Arduino_Interface.h"
#include "MC20_GNSS.h"

#define RGBPIN 10

GNSS gnss = GNSS();

void setup() {
  pinMode(RGBPIN, OUTPUT);
  digitalWrite(RGBPIN, LOW);
  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);

  SerialUSB.begin(115200);

  gnss.Power_On();
  SerialUSB.println("\n\rPower On!");

  if(!gnss.open_GNSS(EPO_QUICK_MODE)){
    return;
  }

  SerialUSB.println("Open GNSS OK.");
  delay(2000);

}

void loop() {
  gnss.dataFlowMode();
  delay(1000);  
}
