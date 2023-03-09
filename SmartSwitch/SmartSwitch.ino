#include "wifi.h"
#include "server.h"

void setup(){
  initWiFi();
  initServer();
}

void loop(){
  handleRequest();  
}
