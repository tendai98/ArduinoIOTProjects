#include <ESP8266WebServer.h>
#include "csm.h"

ESP8266WebServer server(80);


void sendSensorData(){
  AirValue = server.arg(0).toInt();   
  WaterValue = server.arg(1).toInt();
  server.send(200, "text/plain", String(getSoilMoistureValue()));  
}

void initServer(){
  server.on("/status", sendSensorData);
  server.begin();
}

void handleRequest(){
  server.handleClient();
}
