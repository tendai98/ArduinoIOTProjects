#include "SoftwareSerial.h"

SoftwareSerial loraDevice(D3, D2);
String GLOBAL_DATA;

void initLoRA(int baudrate){
  loraDevice.begin(baudrate);
}


void sendRawData(){
  loraDevice.println(GLOBAL_DATA);
}

char recvRawData(){
   return loraDevice.read();
}
