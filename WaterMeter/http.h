#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

void getFlow(){
  server.send(200, "text/plain", String(readFlowRateSensor())+","+String(averageWaterFlow));
}

void _void(){
  server.send(404, "text/plain", "");
}


void initServer(){
  server.on("/data", getFlow);
  server.onNotFound(_void);
  server.begin();
}

void handleRequests(){
  server.handleClient();
}
