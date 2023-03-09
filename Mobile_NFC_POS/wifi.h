#include <ESP8266WiFi.h>

#define ap_name "uNFC"
#define ap_pass "1234567890"

#define HOSTNAME "uNFC"

void initNetwork(){
  WiFi.mode(WIFI_AP);
  WiFi.begin(ap_name, ap_pass);
  while(WiFi.status() != WL_CONNECTED){
    delay(100);
  }
  WiFi.hostname(HOSTNAME);
 // Serial.begin(9600);
 // Serial.println(WiFi.localIP());
}
