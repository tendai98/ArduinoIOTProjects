float lat, lon;
unsigned long age;

#include "const.h"
#include "net.h"
#include "server.h"

char opcode = 0;

void setup(){
  startAPMode(DEV_SSID, DEV_PASS);
  Serial.begin(9600);
  initServer();
}

void executeOpcode(char opcode){
  switch(opcode){
    
    case BIOAUTH_OK_OPCODE:
       enableOTP(true);
       break;
       
    case SEND_GPS_OPCODE:
       parseGPS(&lat, &lon, &age);
       break;
  
  }
}

void loop(){
  runServer();
  while(Serial.available()){
    opcode = Serial.read();
    executeOpcode(opcode);
  }
  delay(10);
}
