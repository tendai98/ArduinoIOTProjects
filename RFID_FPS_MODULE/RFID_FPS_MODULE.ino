#include "fps.h"
#include "rfid.h"

char readCommand(){
  char command = 0;
  while(Serial.available()){
    command = Serial.read();
    if (command == SYS_FLSH_FPS){
          flushFPS();
    }
    //Serial.print("Debug Info: Command => ");Serial.println(command);
  }

  return command;
}

void setup() {
  Serial.begin(9600);
  initRFID();
}

void loop() {
    int id;
    
    switch(readCommand()){
      case SYS_SCAN_MODE:
          id = scanFingerprint();
          Serial.println(id);
          break;

      case SYS_PROG_MODE:
          enrollFingerprints();
          break;

      case SYS_GET_RFID:
          int uid = -1;
          while(uid == -1){
            uid = readCard();
            Serial.println(SYS_RFID_SCAN);
          }
          Serial.println(uid);
          break;
    }

    delay(100);
}
