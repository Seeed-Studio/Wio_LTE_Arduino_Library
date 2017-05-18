#include "MC20_Common.h"
#include "MC20_BT.h"

// GPSTracker gpsTracker = GPSTracker();
BlueTooth bt = BlueTooth();
int bt_state = -1;
int device_id;
char *deviceName = "N-612";

void setup() {
  SerialUSB.begin(115200);
  while(!SerialUSB);

  bt.Power_On();
  SerialUSB.println("\n\rMC20 power On!");
  bt.BTPowerOn();
  SerialUSB.println("\n\rBT power On!");

  while(IDLE != (bt_state = bt.getBTState())){
    SerialUSB.print("State: ");
    SerialUSB.println(bt_state);
    delay(1000);
  }

  device_id = bt.getPairedDeviceID(deviceName);
  if(-1 != device_id){
    SerialUSB.print("\n\r===========================================\n\r");
    SerialUSB.print(deviceName);
    SerialUSB.print(" has been paired already, ID: ");
    SerialUSB.println(device_id);
    SerialUSB.println("===========================================");
  } else {
    SerialUSB.println("BT Scanning...");
    device_id = bt.scanForTargetDevice(deviceName);
    SerialUSB.print("\n\r===============\n\r");
    SerialUSB.print(deviceName);
    SerialUSB.print(" ID: ");
    SerialUSB.println(device_id);
    SerialUSB.println("===============");
  }

  MC20_send_cmd("AT\n\r");  //Push out serial content which blocking in output buffer!
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
