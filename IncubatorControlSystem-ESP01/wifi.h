#include <ESP8266WiFi.h>

char  AP_SSID[] = "ICS-0000000000000001";
char  AP_PASS[] = "ics-12345678";


void initWiFi(){
  WiFi.mode(WIFI_AP);
  WiFi.hostname(AP_SSID);
  WiFi.softAP(AP_SSID, AP_PASS);
}
