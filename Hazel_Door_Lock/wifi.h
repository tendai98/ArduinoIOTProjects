#include <ESP8266WiFi.h>

#define ap_name "Door-Lock"
#define ap_pass "1234567890"

void blinker(){
  digitalWrite(D4, HIGH);
  delay(25);
  digitalWrite(D4, LOW);
  delay(25);
}

void initNetwork(){
  pinMode(D4, OUTPUT);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ap_name, ap_pass);
}
