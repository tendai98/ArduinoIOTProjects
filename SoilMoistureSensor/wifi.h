#include <ESP8266WiFi.h>

#define WIFI_APN "CSM-00000000"

void initWiFi(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP(WIFI_APN);
}
