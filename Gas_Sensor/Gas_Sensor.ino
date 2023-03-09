#include <ESP8266WiFi.h>
#include "client.h"

#define AP_SSID "Mupurwa"
#define AP_PASS "H@ck3rG0tL05t_2020"

void initWiFi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(AP_SSID, AP_PASS);
}

void checkWiFiLink(){
  while(WiFi.status() != WL_CONNECTED){
    delay(100);
  }
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(9600);
  initWiFi();
  checkWiFiLink();
}

void loop() {
  checkWiFiLink();
  httpGet();
}
