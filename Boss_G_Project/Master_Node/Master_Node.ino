#include <ESP8266WiFi.h>
#include<ESP8266WebServer.h>
#include "sonar.h"

ESP8266WebServer server(80);

void notFound() {
  server.send(404,"text/plain","Not Found");
}

#define AP_SSID "NODE-0"
#define AP_PASS "1234567890"

int node0 = 0x0000FFFF;
int node1 = 0x0000FFFF;
int node2 = 0x0000FFFF;

String data;

void proximityCheck(){
  node0 = getDistance();
  if(50 > node0){
    runBuzzer(50);
  }
}

void runBuzzer(int d){
  digitalWrite(D8, HIGH);
  delay(d);
  digitalWrite(D8, LOW);
  delay(d);
}

void getSensors(){
  proximityCheck();
  data = String(node0) + ":";
  data += String(node1) + ":";
  data += String(node2);
  server.send(200,"text/plain", data);
}

void setNode1(){
   node1 = server.arg(0).toInt();
   server.send(200, "text/plain", "OK");
}

void setNode2(){
   node2 = server.arg(0).toInt();
   server.send(200, "text/plain", "OK");
}

void setup() {
  
  WiFi.mode(WIFI_AP); 
  WiFi.softAP(AP_SSID, AP_PASS);
  
  server.on("/sensors", getSensors);
  server.on("/set1", setNode1);
  server.on("/set2", setNode2);
  
  server.onNotFound(notFound);
  server.begin();
  pinMode(D8, OUTPUT);
  startSonar();
  digitalWrite(D8, LOW);
}

void loop() {
  server.handleClient();
  proximityCheck();
}
