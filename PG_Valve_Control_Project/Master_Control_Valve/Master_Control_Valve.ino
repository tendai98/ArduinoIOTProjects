#include "wifi.h"
#include "valve.h"
#include "flowrate.h"
#include "http.h"

void setup(){
  initNetwork();
  initServer();
  initFlowRateSensor();
  initValveControl();
  closeAllValves();
}

void loop(){
  handleRequests();
}
