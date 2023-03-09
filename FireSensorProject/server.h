#include <ESP8266WebServer.h>
#include "temperature.h"
#include "ir.h"

#define LOCATION_INFO "31885 Unit B, Chitungwiza"
#define HTTP_OK 200
#define MIME "text/plain"

ESP8266WebServer server(80);

String data;
bool ALARM_CONTROL = false;
int CURRENT_TEMP = 0;
int LAST_TEMP = 0;

void getData(){
  if(CURRENT_TEMP > 0){
    LAST_TEMP = CURRENT_TEMP;
  }
  data = String(LAST_TEMP)+":"+String(!getIRSensorState())+":"+LOCATION_INFO;
  server.send(HTTP_OK, MIME, data);
}

void resetSensor(){
  ESP.reset();
}

void deadEnd(){
  server.send(404, MIME, "ERROR");
}

void initServer(){
  server.on("/data", getData);
  server.on("/reset", resetSensor);
  server.onNotFound(deadEnd);
  server.begin();
}

void handleRequest(){
  server.handleClient();
}
