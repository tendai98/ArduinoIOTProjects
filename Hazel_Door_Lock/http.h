#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include "rfid.h"

ESP8266WebServer server(80);

int authState = 0;

void setDoorPin(){
  
  EEPROM.begin(8);
  int oldPin = server.arg(0).toInt();
  int newPin = server.arg(1).toInt();
  int storedPin;
  EEPROM.get(0, storedPin);
  
  if(storedPin == oldPin){
    EEPROM.put(0, newPin);
    EEPROM.commit();
    server.send(200, "text/plain", "New Pin Set");
  }else{
    server.send(200, "text/plain", "Access Denied");
  }
}

void authDoorLock(){
  EEPROM.begin(8);
  int storedPin;
  EEPROM.get(0, storedPin);
  int authPin = server.arg(0).toInt();

  int state = -1;

  while(state != 1){
     state = getUID();
     if(state == 3){
       printString("Invalid Key Card");
       delay(1000);
     }else{
      printString("Scanning..."); 
     } 
  }

  printString("Authenticating...");
  delay(1000);
  
  if(storedPin == authPin && state == 1){
      authState = 1;
      server.send(200, "text/plain", "Access Granted");
      printString("Access Granted");
      unlock();
      delay(1000);

    }else{
      server.send(200, "text/plain", "Access Denied");
      printString("Access Denied");
      delay(1000);

  }  
}

void lockDoor(){
  lock();
  authState = 0;
  server.send(200, "text/plain", "Locked");
}

void unlockDoor(){
  if(authState){
    unlock();
    server.send(200, "text/plain", "Unlocked");
  }else{
    server.send(200, "text/plain", "Access Denied");    
  }
}


void getLockState(){
  server.send(200, "text/plain", String(doorLockState));
}

void _void(){
  server.send(404, "text/plain", "");
}


void initServer(){
  server.on("/lock", lockDoor);
  server.on("/unlock", unlockDoor);
  server.on("/setpin", setDoorPin);
  server.on("/auth", authDoorLock);
  server.on("/state", getLockState);
  server.onNotFound(_void);
  server.begin();
  initRFID();
}

void handleRequests(){
  server.handleClient();
}
