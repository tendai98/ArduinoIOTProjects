#include "wifi.h"
#include "http.h"

#define AP_NAME  "Level-Reader"
#define AP_PASS  "12345678"

void setup() {
  startWiFi(AP_NAME, AP_PASS);
  initServer();
}

void loop() {
  handleRequests();
  delay(10);
}
