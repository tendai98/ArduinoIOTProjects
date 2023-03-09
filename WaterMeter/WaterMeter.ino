#include "wifi.h"
#include "flowrate.h"
#include "http.h"

void setup(){
  initNetwork();
  initServer();
  initFlowRateSensor();
}

void loop(){
  calculateAverageFlow();
  handleRequests();
}
