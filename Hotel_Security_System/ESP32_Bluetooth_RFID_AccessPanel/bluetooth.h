#include "BluetoothSerial.h"
#define DEVICE_NAME "ACCESS-PANEL-5"
#define BUFFER_MAX 9

BluetoothSerial RFCOMM;
char RFCOMM_GLOBAL_BUFFER[BUFFER_MAX] = {0,0,0,0,0,0,0,0,0};

void initBluetooth(){
  RFCOMM.begin(DEVICE_NAME);
}

char * recvBTData(){
  
  if(RFCOMM.available()){
    for(int counter = 0; counter < BUFFER_MAX-1; counter++){
      RFCOMM_GLOBAL_BUFFER[counter] = RFCOMM.read();
    }
  }

  return RFCOMM_GLOBAL_BUFFER;
}

void sendBTData(char * dataBuffer){
  RFCOMM.println(dataBuffer);
}

void resetBTBuffer(){
  for(int i=0; i<BUFFER_MAX-1; i++){
    RFCOMM_GLOBAL_BUFFER[i] = 0;
  }
}
