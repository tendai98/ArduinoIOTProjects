#include <ESP8266WiFi.h>
#define BLINK_LED D4

char DEVICE_AP_NAME[] = "Axis";
char DEVICE_AP_PASS[] = "12345678";
char DEVICE_HOSTNAME[] = "axis-1e458a9b";

void blinkLed(short timer){
  digitalWrite(BLINK_LED, !HIGH);
  delay(timer);
  digitalWrite(BLINK_LED, !LOW);
  delay(timer);
}

void initWiFi(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP(DEVICE_AP_NAME, DEVICE_AP_PASS);
  pinMode(BLINK_LED, OUTPUT);
}
