#include "wifi.h"
#include "client.h"

char  ssid[] = "NICK-IOT";
char  pass[] = "asdfghjkl";

void setup() {
  startWiFiHotSpot(ssid, pass);
  pinMode(0, OUTPUT);
  digitalWrite(0, 0);  
}

void loop() {
  getState(GATEWAY_VM_URI);
  if(state){
    digitalWrite(0, 1);
  }else{
    digitalWrite(0, 0);    
  }
  delay(100);
}
