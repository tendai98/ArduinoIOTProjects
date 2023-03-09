#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define OK_RESPONSE_CODE 200
#define ERROR_RESPONSE_CODE 404
#define DATA_MIME "text/plain"
#define RELAY_GPIO 0
#define SERVER_PORT 80

char NET_SSID[] = "SMART-SWITCH-RELAY";
char NET_PASS[] = "qwertyuiop";
ESP8266WebServer server(SERVER_PORT);

void setRelayOnRoute(){
   digitalWrite(RELAY_GPIO, HIGH);
   server.send(OK_RESPONSE_CODE, DATA_MIME, "On");
}

void setRelayOffRoute(){
  digitalWrite(RELAY_GPIO, LOW);  
  server.send(OK_RESPONSE_CODE, DATA_MIME, "Off");
}

void deadEndRoute(){
  server.send(ERROR_RESPONSE_CODE, DATA_MIME, "Not Found");
}

void initializeRelayIO(){
   pinMode(RELAY_GPIO, OUTPUT);
   digitalWrite(RELAY_GPIO, LOW);  
}

void setup() {
  WiFi.mode(WIFI_STA);
  WiFi.softAP(NET_SSID, NET_PASS);
  server.on("/trigger-on", setRelayOnRoute);
  server.on("/trigger-off", setRelayOffRoute);
  server.onNotFound(deadEndRoute);
  server.begin();
  initializeRelayIO();
}

void loop() {
   server.handleClient();  
}
