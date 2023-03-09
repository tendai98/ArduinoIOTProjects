#include "max30100.h"
#include "wifi.h"
#include "gps.h"
#include "misc.h"
#include "http.h"

#define APN "TrackNet"
#define PSS "12345678"


void setup() {
  startWiFi(APN, PSS);
  startSerial(115200);
  initPox();  
  initControls();
  initServer();
  Serial.begin(115200);
}

void loop() {
  updatePox();
  runServer();
  delay(10);
}
