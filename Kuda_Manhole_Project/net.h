#include <WiFi.h>
#define LED 2

const char * brdgAP = "Security";
const char * brdgPD = "1234567890";

void blinkLED(){
    delay(50);
    digitalWrite(LED, LOW);
    delay(50);
    digitalWrite(LED, HIGH);
}

void initDataLink(){
  pinMode(LED, OUTPUT);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(brdgAP, brdgPD);
}
