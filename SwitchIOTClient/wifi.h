#include <ESP8266WiFi.h>

void startWiFiHotSpot(const char * ssid, char * password){
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);     // Run WIFI in AP mode
}
