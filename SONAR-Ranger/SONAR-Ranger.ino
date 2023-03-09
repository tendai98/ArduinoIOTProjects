#include "wifi.h"
#include "sonar.h"
#include "client.h"

#define HOSTNAME "bin-level.herokuapp.com"
#define AP_NAME  "SensorNET"
#define AP_PASS  "12345678"

void setup() {
  startWiFi(AP_NAME, AP_PASS);
  startSonar();
}

void loop() {
  DATA_URL = "/api-1?value="+String(getDistance());
  httpGet(HOSTNAME);
  delay(100);
}
