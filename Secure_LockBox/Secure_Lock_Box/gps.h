#include "SoftwareSerial.h"

SoftwareSerial gps(6,7);

void shutdownGPS(){
  gps.end();
}

void sendGPSData(){
  Serial.write(SEND_GPS_OPCODE);
  delay(1000);
  
  gps.begin(9600);
  while (gps.available()){
    Serial.write(gps.read());
  }
  gps.end();
}
