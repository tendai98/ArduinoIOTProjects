#include <ESP8266WiFi.h>

char * NETWORK_NAME  = "Bulb-Switch";
char * NETWORK_PASSWORD  = "12345678";
char * HOSTNAME = "bulb-0";

void initWiFi(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP(NETWORK_NAME, NETWORK_PASSWORD);
  WiFi.hostname(HOSTNAME);
}
