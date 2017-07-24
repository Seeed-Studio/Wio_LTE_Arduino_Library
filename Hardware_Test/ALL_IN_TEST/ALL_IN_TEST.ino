#include <Arduino.h>
#include "module_common.h"
#include <Wire.h>
#include <SeeedGrayOLED.h>
#include <avr/pgmspace.h>
#include "drawBit.h"
#include "gnss.h"

char buffer[128];
const int BAT_C_PIN = 16;
static long TTS_StartTime = 0;

WioTracker wio = WioTracker();
GNSS gnss = GNSS();

void setDisplayToOriginalState()
{
    SeeedGrayOled.init();
}

void setup(){
    // // Enable Module Power
    // pinMode(wio.MODULE_PWR_PIN, OUTPUT);
    // digitalWrite(wio.MODULE_PWR_PIN , HIGH);    
    // // Enable VCCB
    // pinMode(wio.ENABLE_VCCB_PIN, OUTPUT);
    // digitalWrite(wio.ENABLE_VCCB_PIN, HIGH); 

    // 初始化Grove口串口
	Serial.begin(115200);  // Grove UART
	
	// 模组 POWER_KEY 开机 
	wio.Power_On();
	while(false == wio.Check_If_Power_On()){
		SerialUSB.println("Waitting for module to alvie...");
		delay(1000);
	}  
    SerialUSB.println("Power On O.K!");

    // 打开GPS
    if(!gnss.open_GNSS()) {
    SerialUSB.println("\n\rGNSS init failed!");
        return;
    }
    SerialUSB.println("Open GNSS OK.");
    delay(1000);

    // Init ADC Pin
    // pinMode(4, INPUT_ANALOG);
    // pinMode(5, INPUT_ANALOG);
    // pinMode(6, INPUT_ANALOG);
    // pinMode(7, INPUT_ANALOG);
    pinMode(BAT_C_PIN, INPUT_ANALOG);  // 电池电压模拟引脚

    // GPIO 引脚初始化
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(19, OUTPUT);
    pinMode(20, OUTPUT);
    pinMode(38, OUTPUT);
    pinMode(39, OUTPUT);
    pinMode(22, OUTPUT);
    pinMode(23, OUTPUT);

    
    // OELD 初始化
    Wire.begin();
    SeeedGrayOled.init();


    // Test SerialUSB write
    SerialUSB.println("Start...");

    // Draw image on OELD
    setDisplayToOriginalState();  
	SeeedGrayOled.clearDisplay();
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
    SerialUSB.println("(1) GPIO Blink ");
    digitalWrite(4, pinState);
    digitalWrite(5, pinState);
    digitalWrite(6, pinState);
    digitalWrite(7, pinState);
    digitalWrite(19, pinState);
    digitalWrite(20, pinState);
    digitalWrite(38, pinState);
    digitalWrite(39, pinState);
    digitalWrite(22, pinState);
    digitalWrite(23, pinState);

    // ADC Read Loop
    SerialUSB.print("(2) ");
    SerialUSB.print("ADC4~7: ");
    SerialUSB.print(analogRead(4));
    SerialUSB.print(" ");
    SerialUSB.print(analogRead(5));
    SerialUSB.print(" ");
    SerialUSB.print(analogRead(6));
    SerialUSB.print(" ");
    SerialUSB.println(analogRead(7));
    SerialUSB.print("(3) ");
    SerialUSB.print("BAT_C: ");
    SerialUSB.println(analogRead(BAT_C_PIN));

    // OELD Display ADC 
#if 0    
    SeeedGrayOled.setTextXY(0,0);
    SeeedGrayOled.putString("                ");
    SeeedGrayOled.putString("AIN4: ");
    SeeedGrayOled.putNumber(analogRead(4));
    SeeedGrayOled.setTextXY(1,0);
    SeeedGrayOled.putString("                ");
    SeeedGrayOled.putString("AIN5: ");
    SeeedGrayOled.putNumber(analogRead(5));
    SeeedGrayOled.setTextXY(2,0);
    SeeedGrayOled.putString("                ");
    SeeedGrayOled.putString("AIN6: ");
    SeeedGrayOled.putNumber(analogRead(6));
    SeeedGrayOled.setTextXY(3,0);
    SeeedGrayOled.putString("                ");
    SeeedGrayOled.putString("AIN7: ");
    SeeedGrayOled.putNumber(analogRead(7));
#endif    
    SeeedGrayOled.setTextXY(4,0);
    SeeedGrayOled.putString("                ");
    SeeedGrayOled.putString("BAT_C: ");
    SeeedGrayOled.putNumber(analogRead(BAT_C_PIN)*3300/2048);
    SeeedGrayOled.putString(" mV");

    // Codec test
    if(5000 < (millis() - TTS_StartTime)){
        TTS_StartTime = millis();
        check_with_cmd("AT+QTTS=1, \"6B228FCE4F7F752879FB8FDC6A215757\"\r\n", "+QTTS", CMD, 4, 2000, false);
        delay(2000);
    }
    
    // SIM state
    getSIMState();

    // GNSS
    OLEDDisplayGNSS();

    SerialUSB.println("*************************");

}

void getSIMState()
{
    char *p = NULL;
    char buf_main_info[128];
    
    send_cmd("AT+CPIN?\r\n");
    read_buffer(buffer, 128, 1); 
    // SerialUSB.println(buffer);
    SerialUSB.print("(4) ");
    SerialUSB.print("SIM State: ");
    if(NULL != (p = strstr(buffer, "+CPIN: "))){
        p += 6;
        clean_buffer(buf_main_info, 128);
        uint32_t readTimeStart = millis();
        uint8_t index = 0;
        while(*(p) != '\n'){
            if(1000 < (millis() - readTimeStart)){
                SerialUSB.println("Read buffer timeout!");
                break;
            }
            buf_main_info[index++] = *(p++);
        }
        buf_main_info[index-1] = '\0';
        SerialUSB.println(buf_main_info); 
        SeeedGrayOled.setTextXY(5,0);
        SeeedGrayOled.putString("                ");
        SeeedGrayOled.setTextXY(5,0);    
        SeeedGrayOled.putString("SIMCard: ");
        SeeedGrayOled.putString(buf_main_info);
    }
    else {
        SerialUSB.println("NOT received +CPIN...");
        SeeedGrayOled.setTextXY(5,0);
        SeeedGrayOled.putString("                ");
        SeeedGrayOled.setTextXY(5,0);
        SeeedGrayOled.putString("SIM: ");
        SeeedGrayOled.putString("error!");
    }
}


//GNSS display
void OLEDDisplayGNSS()
{
    SerialUSB.print("(5) GNSS: ");
    if(gnss.getCoordinate()) {
        SerialUSB.print(gnss.str_longitude);
        SerialUSB.print(gnss.West_or_East);
        SerialUSB.print(" , ");
        SerialUSB.print(gnss.str_latitude);
        SerialUSB.println(gnss.North_or_South);
        // Clear 4 rows fow displaying GNSS info
        SeeedGrayOled.setTextXY(6,0);
        SeeedGrayOled.putString("                ");
        SeeedGrayOled.setTextXY(7,0);
        SeeedGrayOled.putString("                ");
        SeeedGrayOled.setTextXY(8,0);
        SeeedGrayOled.putString("                ");
        SeeedGrayOled.setTextXY(6,0);   
        SeeedGrayOled.putString("GNSS: ");
        SeeedGrayOled.setTextXY(7,0);
        SeeedGrayOled.putString(gnss.str_longitude);
        SeeedGrayOled.putString(gnss.West_or_East);
        SeeedGrayOled.setTextXY(8,0);
        SeeedGrayOled.putString(gnss.str_latitude);
        SeeedGrayOled.putString(gnss.North_or_South);
    } else {  
        // Feedback without content of "+QGPSLOC: "
        SerialUSB.println("NOT received +QGPSLOC:");
        SeeedGrayOled.setTextXY(6,0);
        SeeedGrayOled.putString("                ");
        SeeedGrayOled.setTextXY(6,0);
        SeeedGrayOled.putString("GNSS: error!");
    }
}