// #include <Arduino.h>


void setup(){
	Serial.begin(115200);
    SerialUSB.begin(115200);
}

void loop(){
    Serial.println("Hello...");
    SerialUSB.println("Hello...");
    delay(1000);
}