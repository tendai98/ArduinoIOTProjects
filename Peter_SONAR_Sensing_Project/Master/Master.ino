#include <ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include "sonar.h"


ESP8266WebServer server(80);

void notFound() {
  server.send(404,"text/plain","Not Found");
}

#define AP_SSID "Parking-Subnet-0"
#define AP_PASS "1234567890"

int sensor0 = 0x0000FFFF;
int sensor1 = 0x0000FFFF;
int sensor2 = 0x0000FFFF;

String data;
int proximity = 0;

void proximityCheck(){
  proximity = getDistance();
  sensor0 = proximity;
  if(30 > proximity){
    blinkLED(LOW);
  }else{
    blinkLED(HIGH);    
  }
}


void blinkLED(int proximity){
  digitalWrite(D4, proximity);
}

void getSensors(){
  proximityCheck();
  data = String(sensor0) + ":";
  data += String(sensor1) + ":";
  data += String(sensor2);
  server.send(200,"text/plain", data);
}

void setNode1(){
   sensor1 = server.arg(0).toInt();
   server.send(200, "text/plain", "OK");
}

void setNode2(){
   sensor2 = server.arg(0).toInt();
   server.send(200, "text/plain", "OK");
}

void setup() {

  pinMode(D4, OUTPUT);
  digitalWrite(D4, LOW);
  WiFi.mode(WIFI_AP); 
  WiFi.softAP(AP_SSID, AP_PASS);
  
  server.on("/sensors", getSensors);
  server.on("/slave1", setNode1);
  server.on("/slave2", setNode2);
  
  server.onNotFound(notFound);
  server.begin();
  startSonar();
}

void loop() {
  server.handleClient();
  proximityCheck();
}
