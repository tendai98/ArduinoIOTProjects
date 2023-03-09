#include <ESP8266WiFi.h>

char * NETWORK_NAME  = "Lights";
char * NETWORK_PASSWORD  = "qwertyuiop";
char * HOSTNAME = "light-0";

void initWiFi(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP(NETWORK_NAME, NETWORK_PASSWORD);
  WiFi.hostname(HOSTNAME);
}
