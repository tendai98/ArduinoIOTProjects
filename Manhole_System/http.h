#include <WebServer.h>
#include <EEPROM.h>
#include "buzzer.h"
#include "pir.h"
#include "reed.h"
#include "waterlevel.h"

#define HTTP_OK_CODE 200
#define DEFAULT_MIME "text/plain"
#define DEVICE_ID "MH:00000001"
#define SUCCESS_MSG "Operation Complete"
#define LOCATION_INFO "9 Warren Road"

WebServer server(80);

int isSensorArmed = 1;
int authenticated = 0;
int sensorTriggered = 0;

int getSecurityPin(){
  EEPROM.begin(12);
  int pin = 0;
  EEPROM.get(0, pin);
  EEPROM.commit();
  return pin;
}

void getTripState(){
    server.send(HTTP_OK_CODE, DEFAULT_MIME, String(sensorTriggered));
}

void securityAuthentication(){
  int secPin = getSecurityPin();
  int authPin = server.arg(0).toInt();
  if(secPin == authPin){
    authenticated = 1; 
    server.send(HTTP_OK_CODE, DEFAULT_MIME, "Access Granted");
  }else{
    server.send(HTTP_OK_CODE, DEFAULT_MIME, "Access Denied");
  }
}

void setSecurityPin(){
  EEPROM.begin(12);
  int pin = server.arg(0).toInt();
  EEPROM.put(0, pin);
  EEPROM.commit();
  server.send(HTTP_OK_CODE, DEFAULT_MIME, "Security Pin Set");
}

void armSensor(){
  int state = server.arg(0).toInt();
  if(state == 0 && authenticated == 1){
    isSensorArmed = state;
    sensorTriggered = 0;
    server.send(HTTP_OK_CODE, DEFAULT_MIME, "Sensor Disarmed");
  }else{
    if(authenticated != 1){
      server.send(HTTP_OK_CODE, DEFAULT_MIME, "Access Denied");        
    }else{
      isSensorArmed = 1;
      authenticated = 0;
      sensorTriggered = 0;
      server.send(HTTP_OK_CODE, DEFAULT_MIME, "Sensor Is Armed");  
    }  
  }
}

void getSensorState(){
  server.send(HTTP_OK_CODE, DEFAULT_MIME, String(isSensorArmed));
}

void setBuzzer(){
  int d = server.arg(0).toInt();
  runBuzzer(d);
  server.send(HTTP_OK_CODE, DEFAULT_MIME, SUCCESS_MSG);
}

void getPIR(){
  server.send(HTTP_OK_CODE, DEFAULT_MIME, String(getPIRState()));  
}

void getReed(){
  server.send(HTTP_OK_CODE, DEFAULT_MIME, String(getReedSensorState()));
}

void getWaterLevelData(){
  server.send(HTTP_OK_CODE, DEFAULT_MIME, String(getWaterLevel()));
}

void getDeviceId(){
  server.send(HTTP_OK_CODE, DEFAULT_MIME, DEVICE_ID);
}

void getLocationInfo(){
  server.send(HTTP_OK_CODE, DEFAULT_MIME, LOCATION_INFO);
}

void endOfTheLine(){
  server.send(HTTP_OK_CODE, DEFAULT_MIME, "");  
}

void initSensors(){
  initializeBuzzer();
  initializePIRSensor();
  initializeReedSensor();
}

void initServer(){
  initSensors();
  
  server.on("/buzzer", setBuzzer);
  server.on("/pir", getPIR);
  server.on("/id", getDeviceId);
  server.on("/reed",getReed);
  server.on("/waterlevel", getWaterLevelData);
  
  server.on("/armed", getSensorState);
  server.on("/arm", armSensor);
  server.on("/setpin", setSecurityPin);
  server.on("/secauth", securityAuthentication);
  server.on("/tripstate", getTripState);
  server.on("/location", getLocationInfo);
  
  server.onNotFound(endOfTheLine);
  server.begin();
}

void runServer() {
  server.handleClient();
}
