#define NODE_URL "http://192.168.4.1/set1?state="
#define AP_SSID "NODE-0"
#define AP_PASS "1234567890"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include "sonar.h"

HTTPClient http;
WiFiClient client;

int state = 0;

void runBuzzer(int d){
  digitalWrite(D8, HIGH);
  delay(d);
  digitalWrite(D8, LOW);
  delay(d);
}

void proximityCheck(){
  state = getDistance();
  if(50 > state){
    runBuzzer(100);
    blinkLED(LOW);
  }else{
    blinkLED(HIGH);    
  }
}


void blinkLED(int state){
  digitalWrite(D4, state);
}

void sendSensorState(){
  proximityCheck();
  http.begin(client, String(NODE_URL)+String(state));
  http.GET();
  http.end();
}

void setup(){
    startSonar();
    pinMode(D4, OUTPUT);
    WiFi.mode(WIFI_STA);
    WiFi.begin(AP_SSID, AP_PASS);
    while(WiFi.status() != WL_CONNECTED){
      delay(100);  
      digitalWrite(D4, HIGH);
      delay(100);
      digitalWrite(D4, LOW);
    }

  pinMode(D8, OUTPUT);
  digitalWrite(D4, HIGH);
  digitalWrite(D8, LOW);
}

void loop(){
  sendSensorState();
  proximityCheck();
  delay(10);
}
