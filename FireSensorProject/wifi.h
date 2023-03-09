#include <ESP8266WiFi.h>

#define AP_NAME "Fire-Monitoring-System"
#define AP_PASS "1234567890"

#define BLINK_LED D4

void blinkLED(){
  digitalWrite(BLINK_LED, LOW);  
  delay(50);
  digitalWrite(BLINK_LED, HIGH);
  delay(50);
}

void initNET(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_NAME, AP_PASS);
  pinMode(BLINK_LED, OUTPUT);
}
