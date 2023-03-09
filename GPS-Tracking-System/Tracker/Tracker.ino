#include "wifi.h"
#include "client.h"

void setup(){
  startWiFi();
  initGPS();
}

void loop(){
  getLocationData();
  httpGet();
  delay(500);
}
