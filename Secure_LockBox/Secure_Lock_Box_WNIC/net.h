#include <ESP8266WiFi.h>
#include <TinyGPS.h>

TinyGPS gps;

void parseGPS(float * lat, float * lon, unsigned long * age){
  while (Serial.available()){
    if(gps.encode(Serial.read())){
       gps.f_get_position(lat, lon, age);
    }
  }
}

void startAPMode(char * ssid, char * password){
  WiFi.softAP(ssid, password);
}

void startClientMode(char * ssid, char * password){
  WiFi.begin(ssid, password);
}
