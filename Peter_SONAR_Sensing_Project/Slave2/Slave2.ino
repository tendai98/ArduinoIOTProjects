#define MASTER_URL "http://192.168.4.1/slave1?proximity="

#define AP_SSID "Parking-Subnet-0"
#define AP_PASS "1234567890"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>
#include "sonar.h"

HTTPClient http;
WiFiClient client;

int proximity = 0;

void proximityCheck(){
  proximity = getDistance();
  if(30 > proximity){
    blinkLED(LOW);
  }else{
    blinkLED(HIGH);    
  }
}


void blinkLED(int proximity){
  digitalWrite(D4, proximity);
}

void sendSensorState(){
  proximityCheck();
  http.begin(client, String(MASTER_URL)+String(proximity));
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
