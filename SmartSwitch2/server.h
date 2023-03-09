#include <ESP8266WebServer.h>

#define RELAY_GPIO_0 0
#define RELAY_GPIO_1 2
ESP8266WebServer server(80);

void relayOn(){
  digitalWrite(RELAY_GPIO_0, HIGH);
  digitalWrite(RELAY_GPIO_1, HIGH);
  server.send(200, "text/plain", "LIGHT-ON");
}

void relayOff(){
  digitalWrite(RELAY_GPIO_0, LOW);
  digitalWrite(RELAY_GPIO_1, LOW);
  server.send(200, "text/plain", "LIGHT-OFF");  
}

void initRelayGPIO(){
  pinMode(RELAY_GPIO_0, OUTPUT);
  pinMode(RELAY_GPIO_1, OUTPUT);
  relayOff();
}

void initServer(){
  initRelayGPIO();
  server.on("/on", relayOn);
  server.on("/off", relayOff);
  server.begin();
}

void handleRequest(){
  server.handleClient();
}
