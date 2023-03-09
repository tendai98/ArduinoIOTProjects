#include "alarm.h"
#include "wifi.h"
#include "server.h" 

#define MAX_TEMP 35

void setup(){
  setupTemperatureSensor();
  setupIRSensor();
  initNET();
  initServer();
  initAlarm();
}

void serveData(){
  CURRENT_TEMP = getTempValue();
 
  if(CURRENT_TEMP > 0 && CURRENT_TEMP > MAX_TEMP){
    ALARM_CONTROL = true;
  }
  
  if(ALARM_CONTROL){
    triggerAlarm();
  }
   handleRequest();
}

void loop(){
  serveData();
}
