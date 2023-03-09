#include <ESP8266WebServer.h>
#include "sonar.h"

ESP8266WebServer server(80);

void getData(){
  server.send(200, "text/plain", String(getDistance()));
}

void initServer(){
  server.on("/data", getData);
  server.begin();
  startSonar();
}

void handleRequests(){
  server.handleClient();
  delay(100);
}
