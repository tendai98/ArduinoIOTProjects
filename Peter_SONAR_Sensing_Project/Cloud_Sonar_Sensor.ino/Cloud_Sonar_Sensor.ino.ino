#include "wifi.h"
#include "firebase.h"
#include "hardware.h"


#define AP_SSID           "SensorNet"
#define AP_PASS           "12345678"
#define MODULE_ID         "PARK-BAY:0000000000000000"
#define VALUE_NODE        "/sensorValue"
#define COMMD_NODE        "/cmdValue"      
#define RETRY_DELAY       100

#define SYSTEM_LED_ON     0x1FA0
#define SYSTEM_LED_OFF    0x1FA1
#define SYSTEM_REBOOT     0x1FA2

String path;
int value;

void executeCommand(int opcode){
  
  Serial.println(value, HEX);
    
  switch(opcode){
      case SYSTEM_LED_ON:
          controlLed(HIGH);
          break;

      case SYSTEM_LED_OFF:
          controlLed(LOW);
          break;

      case SYSTEM_REBOOT:
          ESP.reset();
          break;
  }
}

void setup() {
  
  Serial.begin(9600);
  wifi_up(AP_SSID, AP_PASS, RETRY_DELAY);
  hardware_up();
  Firebase_up();
  
  path = String(MODULE_ID COMMD_NODE);
  set(path, 0);
  
}

void loop() {

    path = String(MODULE_ID VALUE_NODE);
    value = readValue();
    set(path, value);
    
    path = String(MODULE_ID COMMD_NODE);
    value = get(path);
    executeCommand(value);
    
    delay(100);
}
