#include <ESP8266WiFi.h>

#define ap_name "Watermeter-0001"
#define ap_pass "1234567890"

void initNetwork(){
 WiFi.mode(WIFI_STA);
  WiFi.softAP(ap_name, ap_pass);
  digitalWrite(D4, HIGH);
}
