#include <ESP8266WiFi.h>

void initWiFi(char * ssid, char * password){
  WiFi.hostname("DHT11Server");
  WiFi.softAP(ssid, password);
}
