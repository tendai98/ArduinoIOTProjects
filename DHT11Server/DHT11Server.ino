#include "wifi.h"
#include "server.h"

void setup() {
  initWiFi("DHT11-0000", "12345678");
  initServer();
}

void loop() {
 handleRequest();
 delay(100);
}
