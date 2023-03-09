#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>

#define RELAY_GPIO_1 0
#define RELAY_GPIO_2 2
#define RELAY_DEVICE_ID "RELAY"

#define HTTP_OK_CODE 200
#define HTTP_404_CODE 404
#define MIME_TYPE "text/plain"

const char* ssid = "Shoe-Detector";
const char* password = "asdfghjkl";

ESP8266WebServer server(80);

void switchRelayOn(){
  digitalWrite(RELAY_GPIO_1, HIGH);
  digitalWrite(RELAY_GPIO_2, HIGH);
  server.send(HTTP_OK_CODE, MIME_TYPE, "Relay Online");
}

void switchRelayOff(){
  digitalWrite(RELAY_GPIO_1, LOW);
  digitalWrite(RELAY_GPIO_2, LOW);
  server.send(HTTP_OK_CODE, MIME_TYPE, "Relay Offlne");
}

void initializeRelay(){
  pinMode(RELAY_GPIO_1, OUTPUT);
  pinMode(RELAY_GPIO_2, OUTPUT);
  switchRelayOff();
}

void getDeviceId(){
  server.send(HTTP_OK_CODE, MIME_TYPE, RELAY_DEVICE_ID);
}

void noOperation(){
  server.send(HTTP_404_CODE, MIME_TYPE, "Operation Not Supported");
}

void initializeServer(){
  server.on("/on", switchRelayOn);
  server.on("/off", switchRelayOff);
  server.on("/id", getDeviceId);
  server.onNotFound(noOperation);
  server.begin();
}

void processRequests(){
  server.handleClient();
}

void setupConnection(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);  
}

void connectToNetwork(){
  if(WiFi.status() != WL_CONNECTED){
    setupConnection();
  }

  while(WiFi.status() != WL_CONNECTED){
    delay(100);
  }
}

void setup() {
  initializeRelay();
  connectToNetwork();
  initializeServer();
}

void loop() {
  connectToNetwork();
  processRequests();
}
