#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

String data = "";

void _x(){
  server.send(200, "text/plain", "");  
}

void getHealthData(){
  data = String(getHeartRate());
  data += ":"+String(getO2());
  data += ":"+String(getButton());
  server.send(200, "text/plain", data);  
}

void getLocationData(){
  data = String(getLatitude());
  data += ":"+String(getLongitude());
  server.send(200, "text/plain", data); 
}

void initServer(){
  server.on("/health", getHealthData);
  server.on("/location", getLocationData);
  server.onNotFound(_x);
  server.begin();
}

void runServer(){
  server.handleClient();
};
