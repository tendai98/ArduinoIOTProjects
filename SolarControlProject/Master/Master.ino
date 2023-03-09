#include <ESP8266WiFi.h>

char AP_NAME[] = "SolarControlSystem";
char AP_PSK[] = "1234567890";

void initWiFiNet(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_NAME, AP_PSK);
}

void setup(){
  initWiFiNet();  
}
void loop(){}
