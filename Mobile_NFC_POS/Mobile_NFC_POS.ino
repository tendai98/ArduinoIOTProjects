#include "display.h"
#include "wifi.h"
#include "http.h"

void coreInit(){
  initOLED();
  runBootAnimation();
  printString("uNFC v1.0");
  delay(3000);
  printString("CONNECTING...");
  initNetwork();
}

void checkNetworkConnection(){
   while(WiFi.status() != WL_CONNECTED){
    printString("RECONNECTING...");
    delay(100);
  }
}

void setup(){
  coreInit();
  initServer();
  delay(1000);
}

void loop() {
  handleRequests();
  printString("Place a card");
  delay(100);
  checkNetworkConnection();
}
