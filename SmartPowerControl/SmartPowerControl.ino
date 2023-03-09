#include "power.h"
#include "wifi.h"
#include "server.h"

void setup(){
    initACS();
    initWiFi();
    startServer();
}

void loop(){
      scanServerData(); 
      delay(100);
}
