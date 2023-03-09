#include "power.h"
#include "lora.h"
#include "relay_control.h"

char opcode;

void setup(){
    initACS();
    initLoRA(9600);
    initControlRelays();
}

void loop(){

      while(loraDevice.available()){     
        GLOBAL_DATA = String(currentReading())+",";
        GLOBAL_DATA += String(RELAY_1)+",";
        GLOBAL_DATA += String(RELAY_2)+",";
        GLOBAL_DATA += String(deviceMode);
        
        sendRawData();
        opcode = recvRawData();
        systemControl(opcode);
        controlRelay(opcode);
        delay(100);
      }
}
