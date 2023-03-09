#include "rfid.h"
#include "BluetoothSerial.h"

#define DEVICE_NAME "ROOM-N5" 

int opcode = 0;
int returnOpcode = 0;
BluetoothSerial RFCOMM;

void setup(){
  initRFID();  
  RFCOMM.begin(DEVICE_NAME);
}

void loop(){
  int i = 0;
  bool isDataDumped = false, dataAvailable = false;
  opcode = RFCOMM.available() ? (int) RFCOMM.read() : 0;
  
  switch(opcode){

      case RFID_PUSH_DATA_OPCODE:
        i = 0;
        while (RFCOMM.available()){
           if(!dataAvailable){
              dataAvailable = true;
              RFCOMM.printf("DATA:");
           }
           GLOBAL_DATA_BLOCK[i] = (byte) RFCOMM.read();
           RFCOMM.printf("%c", (char) GLOBAL_DATA_BLOCK[i]);
           i++; 
           isDataDumped = true;
           if(i==16){
             break;
           }
        }
        
        if(isDataDumped){        
          RFCOMM.println();
          RFCOMM.printf("ERROR:%x\n", RFID_OPRX_SUCCES_CODE);
        }else{         
          RFCOMM.printf("ERROR:%x\n", RFID_OPRX_FAILED_CODE);
        }
        break;

      case RFID_PULL_DATA_OPCODE:
        RFCOMM.printf("DATA:");
        for(i = 0; i<16; i++){
           RFCOMM.printf("%c", (char) GLOBAL_DATA_BUFFER[i]); 
        }
        RFCOMM.println();
        break;
          
      case RFID_READ_OPCODE_CODE:
        returnOpcode = readRFIDData();
        RFCOMM.printf("ERROR:%x\n",returnOpcode);
        break;

      case RFID_WRIT_OPCODE_CODE:
        returnOpcode = writeRFIDData();
        RFCOMM.printf("ERROR:%x\n",returnOpcode);
        break;    

      case RFID_RESET_MCU_OPCODE:
        RFCOMM.printf("ERROR:%x\n", RFID_RESET_MCU_OPCODE);
        delay(3000);
        ESP.restart();
        break;
  }

  delay(10);
}
