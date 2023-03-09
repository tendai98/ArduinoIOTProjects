#include <ESP8266WiFi.h>
#define AP_SSID "Controller-0"
#define AP_PASS "root12345"

void initWiFi(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID,AP_PASS);
}
