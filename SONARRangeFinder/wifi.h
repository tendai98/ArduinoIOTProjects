#include <ESP8266WiFi.h>
#define FLASH_LED_GPIO D4

void startWiFi(char * ssid, char * password){
  WiFi.hostname("LEVEL-0");
  WiFi.mode(WIFI_AP);
  pinMode(FLASH_LED_GPIO, OUTPUT);
  WiFi.softAP(ssid, password);
}
