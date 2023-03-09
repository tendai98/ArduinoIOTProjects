#include "display.h"
#include "relay.h"
#include "wifi.h"
#include "http.h"

void setup() {
  initOLED();
  initNetwork();
  initServer();
  initLockControl();
}

void loop() {
  handleRequests();
  if(doorLockState){
    printString("[!] Locked");
    blinker();
  }else{
    printString("[*] Unlocked");
  }
}
