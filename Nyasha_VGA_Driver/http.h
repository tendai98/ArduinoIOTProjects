#include <WebServer.h>
#include <EEPROM.h>

#include "vga.h"
#include "hardware.h"

#define HTTP_OK_CODE 200
#define SUCCESS_MSG "OK"
#define DEFAULT_MIME "text/plain"
#define BUFFER_MAX 53

WebServer server(80);
char dataBuffer[BUFFER_MAX];
bool isAuthenticated = false;

void setSecurityPin(){
  int oldPin, newPin, romPin;

  oldPin = server.arg(0).toInt();
  newPin = server.arg(1).toInt();
  
  EEPROM.begin(8);
  EEPROM.get(0, romPin);
  
  if(oldPin == romPin){
    EEPROM.put(0, newPin);
    EEPROM.commit();
    server.send(HTTP_OK_CODE, DEFAULT_MIME, "Pin Set");
  }else{
    server.send(HTTP_OK_CODE, DEFAULT_MIME, "Access Denied");    
  }
}

void authenticateUser(){
  int userPin, romPin;
  userPin = server.arg(0).toInt();
  EEPROM.begin(8);
  EEPROM.get(0, romPin);
  EEPROM.commit();

  if(userPin == romPin){
     isAuthenticated = true;
     server.send(HTTP_OK_CODE, DEFAULT_MIME, "Access Granted");
  }else{
    isAuthenticated = false;
   server.send(HTTP_OK_CODE, DEFAULT_MIME, "Access Denied");
  }
}

void lockDisplayAccess(){
  int userPin, romPin;
  userPin = server.arg(0).toInt();
  EEPROM.begin(8);
  EEPROM.get(0, romPin);
  EEPROM.commit();

  if(userPin == romPin){
     isAuthenticated = false;
     server.send(HTTP_OK_CODE, DEFAULT_MIME, "Device Locked");
  }else{
   server.send(HTTP_OK_CODE, DEFAULT_MIME, "Access Denied");
  }
}

void pushMessage(){
  if(isAuthenticated){
    server.arg(0).toCharArray(dataBuffer, BUFFER_MAX);
    vgaPrintBuff(dataBuffer);
    server.send(HTTP_OK_CODE, DEFAULT_MIME, SUCCESS_MSG);
  }else{
   server.send(HTTP_OK_CODE, DEFAULT_MIME, "Access Denied");
  }
}

void clearScreen(){
  if(isAuthenticated){
    vgaClear();
     server.send(HTTP_OK_CODE, DEFAULT_MIME, SUCCESS_MSG);
  }else{
    server.send(HTTP_OK_CODE, DEFAULT_MIME, "Access Denied");
  }
}

void alertSystem(){
  if(isAuthenticated){
    driveAlert();
    server.send(HTTP_OK_CODE, DEFAULT_MIME, SUCCESS_MSG);
  }else{
    server.send(HTTP_OK_CODE, DEFAULT_MIME, "Unauthorized");      
  }
}

void resetSystem(){
  if(isAuthenticated){    
      server.send(HTTP_OK_CODE, DEFAULT_MIME, "Rebooting...");
      delay(4000);
      ESP.restart();
  }else{
    server.send(HTTP_OK_CODE, DEFAULT_MIME, "Unauthorized");    
  }
}

void deadEnd(){
  server.send(HTTP_OK_CODE, DEFAULT_MIME, "");
}

void initAPIServer(){
  
  server.on("/push", pushMessage);
  server.on("/clear", clearScreen);
  server.on("/alert", alertSystem);
  server.on("/reset", resetSystem);
  server.on("/auth", authenticateUser);
  server.on("/pin", setSecurityPin);
  server.on("/lock", lockDisplayAccess);
  
  server.onNotFound(deadEnd);
  server.begin();
}

void handleInboundRequests(){
  server.handleClient();
  delay(1);
}
