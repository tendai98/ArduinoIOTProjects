#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer web(8080);
int state = 0;
const int RELAY_PIN_0 =  D3;
const int RELAY_PIN_1  = D4;
char AP_NAME[] = "Group-7-Project";
char AP_PSK[] = "1234567890";

void setRelayState(){
  state = web.arg(0).toInt();
  digitalWrite(RELAY_PIN_0, state);  
  digitalWrite(RELAY_PIN_1, state);
  web.send(200, "text/plain", state == 1 ? "ON" : "OFF");
}

void initRelayGPIO(){
  pinMode(RELAY_PIN_0, OUTPUT);
  pinMode(RELAY_PIN_1, OUTPUT);
  digitalWrite(RELAY_PIN_0, LOW);  
  digitalWrite(RELAY_PIN_1, LOW);
}

void initWiFiNet(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_NAME, AP_PSK);
}

void setup(){
  initWiFiNet();
  initRelayGPIO();
  web.on("/state", setRelayState);
  web.begin();  
}

void loop(){
  web.handleClient();
}
