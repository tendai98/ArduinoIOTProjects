#include "relay.h"
#include "sonar.h"
#include "http.h"

#include <ESP8266WiFi.h>

#define AP_SSID "Control-0"
#define AP_PASS "1234567890"

#define GAS_SENSOR_GPIO   D5
#define REED_SENSOR_GPIO  D6

void initBus(){
  pinMode(GAS_SENSOR_GPIO, INPUT);
  pinMode(REED_SENSOR_GPIO, INPUT);
}

void startWiFi(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP(AP_SSID, AP_PASS);
}

void setup(){
    initBus();
    startWiFi();
    initSonar();
    initRelayControl();
    initWebServer();
}

void loop(){
  
  if(50 > getDistance()){
    activate();
  }else{
    deactivate();
  }

  handleClients();
  delay(1);
}
