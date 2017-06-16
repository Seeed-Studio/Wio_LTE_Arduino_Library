#include <Arduino.h>
#include "module_common.h"

WioTracker wio = WioTracker();

void setup(){
    pinMode(wio.ENABLE_VCCB_PIN, OUTPUT);
    digitalWrite(wio.ENABLE_VCCB_PIN, HIGH);
    pinMode(4, INPUT_ANALOG);
    pinMode(5, INPUT_ANALOG);
    pinMode(6, INPUT_ANALOG);
    pinMode(7, INPUT_ANALOG);

    SerialUSB.begin(115200);
}

void loop(){
    SerialUSB.print("ADC4~7： ");
    SerialUSB.print(analogRead(4));
    SerialUSB.print(" ");
    SerialUSB.print(analogRead(5));
    SerialUSB.print(" ");
    SerialUSB.print(analogRead(6));
    SerialUSB.print(" ");
    SerialUSB.println(analogRead(7));
    delay(1000);
}