#include <ESP8266WebServer.h>
#include "dht.h"

#define HTTP_OK_CODE 200
#define DEFAULT_MIME "text/plain"

ESP8266WebServer server(80);

void sendTemperature(){
  server.send(HTTP_OK_CODE, DEFAULT_MIME, String(getTemperature()));
}

void sendHumidity(){
  server.send(HTTP_OK_CODE, DEFAULT_MIME, String(getHumidity()));  
}

void initServer(){
  initSensor();
  server.on("/temperature", sendTemperature);
  server.on("/humidity", sendHumidity);
  server.begin();
}

void handleRequest(){
  server.handleClient();
}
