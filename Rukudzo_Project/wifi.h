#include <ESP8266WiFi.h>

void startWiFi(char * ssid, char * password){
  WiFi.mode(WIFI_AP);
  WiFi.hostname("tracker1");
  WiFi.softAP(ssid, password);
}
