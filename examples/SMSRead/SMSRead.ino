#include "wio_tracker.h"

uint16_t newSMSNumber = -1;
char message[128];
char phone[32];
char dateTime[32];


WioTracker wio = WioTracker();

void setup() {
    wio.Power_On();
    SerialUSB.println("Power On!");
    SerialUSB.println("Wait for network registered...");

    if (!wio.waitForNetworkRegister()) {
        SerialUSB.println("Network error!");
        return;
    } else {
        SerialUSB.println("Network ready!");
    }
    wio.readAllRecUnreadSMS();  // Set all "REC UNREAD SMS" to "REC READ SMS"
}

void loop() {
    int id = wio.detectRecUnreadSMS();
    if (-1 != id) {
        newSMSNumber = id;
        wio.readSMS(newSMSNumber, message, 128, phone, dateTime);
        SerialUSB.println("++++++++++++++ Start +++++++++++++++++");
        SerialUSB.print("From: ");
        SerialUSB.println(phone);
        SerialUSB.print("Date: ");
        SerialUSB.println(dateTime);
        SerialUSB.println(message);
        SerialUSB.println("++++++++++++++++ End +++++++++++++++");
    } else {
        SerialUSB.println("Waiting for new SMS!");
    }

    delay(1000);
}
