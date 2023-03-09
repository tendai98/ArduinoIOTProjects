#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

int sonar = 0;
int reed = 0;
int gas = 0;
String data = "";

void readSensors(){
  sonar = getDistance();
  gas = digitalRead(D5);
  reed = digitalRead(D6);
}

void getSensorData(){
  readSensors();
  data = String(sonar)+":"+String(reed)+":"+String(!gas);
  server.send(200, "text/plain", data);
}

void resetSystem(){
  ESP.reset();
}

void initWebServer(){
  server.on("/sensors", getSensorData);
  server.on("/reset", resetSystem);
  server.begin();
}

void handleClients(){
  server.handleClient();
}
