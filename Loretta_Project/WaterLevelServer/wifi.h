#define ESP_SSID              "WLS-0"
#define ESP_PASS              "1234567890"

#include <ESP8266WiFi.h>

// Run to setup WIFI 

void initWiFi(){
  digitalWrite(D0, LOW);
  WiFi.softAP(ESP_SSID, ESP_PASS);    // Put the device into SoftAP Mode
}
