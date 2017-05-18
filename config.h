#include <Arduino.h>

#define ENABLE_VCCB_PIN             26
#define MODULE_PWR_PIN       18
#define PWR_KEY_PIN          36

#define WAKEUP_IN_PIN         32
#define AP_READY_PIN          33
#define WAKEUP_DISABLE_PIN    34 
#define RESET_MODULE_PIN      35     
#define STATUS_PIN            31


#define PIN_INIT() (\
pinMode(PWR_KEY_PIN, OUTPUT);\
pinMode(MODULE_PWR_PIN, OUTPUT);\
pinMode(ENABLE_VCCB_PIN, OUTPUT);\
pinMode(RESET_MODULE_PIN, OUTPUT);\
pinMode(STATUS_PIN, INPUT);\

digitalWite(PWR_KEY_PIN, HIGH);\
digitalWite(MODULE_PWR_PIN, LOW);\
digitalWite(ENABLE_VCCB_PIN, LOW);\
digitalWite(RESET_MODULE_PIN, LOW);\
)

