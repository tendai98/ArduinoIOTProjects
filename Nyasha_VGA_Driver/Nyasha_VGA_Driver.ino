#include "wifi.h"
#include "http.h"

void setup() {
  initWiFiAP();
  initHardware();
  initVGA();
  initAPIServer();

  vgaPrintBuff(INTRO_BANNER);
  vgaPrintLine();
}

void loop() { 
  handleInboundRequests();
}
