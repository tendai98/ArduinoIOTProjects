#include <ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include "sonar.h"


ESP8266WebServer server(80);

void notFound() {
  server.send(404,"text/plain","Not Found");
}

#define AP_SSID "HotelSensorGrid"
#define AP_PASS "1234567890"

String data;
int proximity1 = 0;
int proximity2 = 0;
int proximity3 = 0;
int proximity4 = 0;

void proximityDataAquisition(){
  proximity1 = getSonar1Distance();
  proximity2 = getSonar2Distance();
  proximity3 = getSonar3Distance();
  proximity4 = getSonar4Distance();
}


void blinkLED(){
  digitalWrite(D4, LOW);
  delay(25);
  digitalWrite(D4, HIGH);
  delay(25);
}

void getSensors(){
  proximityDataAquisition();

  data = "";
  data += String(proximity1) + ":";
  data += String(proximity2) + ":";
  data += String(proximity3) + ":";
  data += String(proximity4);
  
  server.send(200,"text/plain", data);
}


void setup() {

  WiFi.mode(WIFI_AP); 
  WiFi.softAP(AP_SSID, AP_PASS);
  
  pinMode(D4, OUTPUT);
  digitalWrite(D4, LOW);

  initSonar1();
  initSonar2();
  initSonar3();
  initSonar4();
  
  server.on("/sensors", getSensors);
  server.onNotFound(notFound);
  server.begin();

}

void loop() {
  server.handleClient();
  blinkLED(); 
}
