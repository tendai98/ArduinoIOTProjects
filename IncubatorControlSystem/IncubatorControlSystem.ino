#include "wifi.h"
#include "dht.h"
#include "relays.h"
#include "mcp.h"
#include "server.h"


void setup(){
  initWiFi();
  initServer();
  initMCP();
  initDHT();
  initRelays();
}

void loop(){
  
  getSensorData();
  if(!SYSTEM_CONTROL_OVERRIDE){
    runMCP();
  }
  handleRequest();
}
