#include <Arduino.h>
#include "module_common.h"
#include <Wire.h>
#include <SeeedGrayOLED.h>
#include <avr/pgmspace.h>
#include "drawBit.h"

const int BAT_C_PIN = 16;
static long TTS_StartTime = 0;

WioTracker wio = WioTracker();


void setDisplayToOriginalState()
{
    SeeedGrayOled.init();
}

void setup(){
    // Enable Module Power
    pinMode(wio.MODULE_PWR_PIN, OUTPUT);
    digitalWrite(wio.MODULE_PWR_PIN , HIGH);    
    // Enable VCCB
    pinMode(wio.ENABLE_VCCB_PIN, OUTPUT);
    digitalWrite(wio.ENABLE_VCCB_PIN, HIGH);

    // Serial port init
	Serial.begin(115200);  // Grove UART
	
	// Module power on
	wio.Power_On();
	while(false == wio.Check_If_Power_On()){
		SerialUSB.println("Waitting for module to alvie...");
		delay(1000);
	}  
    SerialUSB.println("Power On O.K!");

    // Init ADC Pin
    pinMode(4, INPUT_ANALOG);
    pinMode(5, INPUT_ANALOG);
    pinMode(6, INPUT_ANALOG);
    pinMode(7, INPUT_ANALOG);
    pinMode(BAT_C_PIN, INPUT_ANALOG);

    // Init Grove digital Pins
    pinMode(19, OUTPUT);
    pinMode(20, OUTPUT);
    pinMode(38, OUTPUT);
    pinMode(39, OUTPUT);
    
    // OELD init
    Wire.begin();
    SeeedGrayOled.init();


    // Test SerialUSB write
    SerialUSB.println("Start...");

    // Draw image on OELD
    setDisplayToOriginalState();  
	SeeedGrayOled.clearDisplay();
	//Draw binary Bitmap
	SeeedGrayOled.drawBitmap(image1,128*128/8);
    SeeedGrayOled.drawBitmap(image2,128*128/8);
    SeeedGrayOled.drawBitmap(SeeedLogo,128*128/8);
    SeeedGrayOled.drawBitmap(wioTracker,128*128/8);
    delay(1000);
    SeeedGrayOled.clearDisplay();     //Clear Display.
    SeeedGrayOled.setNormalDisplay(); //Set Normal Display Mode
    SeeedGrayOled.setVerticalMode();  // Set to vertical mode for displaying text

    // SDCard Test
    

    TTS_StartTime = millis();
}

void loop(){

    // GPIO Blink Loop
    static int pinState = 1;
    pinState ^= 1;

    digitalWrite(19, pinState);
    digitalWrite(20, pinState);
    digitalWrite(38, pinState);
    digitalWrite(39, pinState);

    // ADC Read Loop
    SerialUSB.print("ADC4~7: ");
    SerialUSB.print(analogRead(4));
    SerialUSB.print(" ");
    SerialUSB.print(analogRead(5));
    SerialUSB.print(" ");
    SerialUSB.print(analogRead(6));
    SerialUSB.print(" ");
    SerialUSB.println(analogRead(7));
    SerialUSB.print("BAT_C: ");
    SerialUSB.println(analogRead(BAT_C_PIN));

    // OELD Display ADC 
    SeeedGrayOled.setTextXY(5,0);
    SeeedGrayOled.putString("                ");
    SeeedGrayOled.putString("AIN4: ");
    SeeedGrayOled.putNumber(analogRead(4));
    SeeedGrayOled.setTextXY(6,0);
    SeeedGrayOled.putString("                ");
    SeeedGrayOled.putString("AIN5: ");
    SeeedGrayOled.putNumber(analogRead(5));
    SeeedGrayOled.setTextXY(7,0);
    SeeedGrayOled.putString("                ");
    SeeedGrayOled.putString("AIN6: ");
    SeeedGrayOled.putNumber(analogRead(6));
    SeeedGrayOled.setTextXY(8,0);
    SeeedGrayOled.putString("                ");
    SeeedGrayOled.putString("AIN7: ");
    SeeedGrayOled.putNumber(analogRead(7));
    SeeedGrayOled.setTextXY(9,0);
    SeeedGrayOled.putString("                ");
    SeeedGrayOled.putString("BAT_C: ");
    SeeedGrayOled.putNumber(analogRead(BAT_C_PIN)*3300/2048);
    SeeedGrayOled.putString(" mV");

    // Codec test
    if(4000 < (millis() - TTS_StartTime)){
        TTS_StartTime = millis();
        check_with_cmd("AT+QTTS=1, \"6B228FCE4F7F752879FB8FDC6A215757\"\r\n", "OK", CMD, 4, 2000, true);
    }
    delay(500);
}