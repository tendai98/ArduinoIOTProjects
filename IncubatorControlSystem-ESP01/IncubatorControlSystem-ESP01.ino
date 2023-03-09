#include "wifi.h"
#include "relays.h"
#include "mcp.h"
#include "server.h"


void setup(){
  initWiFi();
  initServer();
  initMCP();
  initRelays();
}

void loop(){
    
  if(!SYSTEM_CONTROL_OVERRIDE){
    runMCP();
  }
  handleRequest();
}
