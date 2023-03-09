#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

void closeAllValves(){
  shutDownValve();
  server.send(200, "text/plain", "Valve Shutdown Complete");
}

void openAllValves(){
  openValve();
  server.send(200, "text/plain", "All Valves Openned");
}

void controlMasterValve(){
  int state = server.arg(0).toInt();
  executeValveControl(state);
  server.send(200, "text/plain", "Valve Configured");
}


void getValveState(){
  server.send(200, "text/plain", String(masterValveState));
}

void getFlow(){
  server.send(200, "text/plain", String(readFlowRateSensor()));
}

void _void(){
  server.send(404, "text/plain", "");
}


void initServer(){
  server.on("/control", controlMasterValve);
  server.on("/shutdown", closeAllValves);
  server.on("/openall", openAllValves);
  server.on("/state", getValveState);
  server.on("/flow", getFlow);
  server.onNotFound(_void);
  server.begin();
}

void handleRequests(){
  server.handleClient();
}
