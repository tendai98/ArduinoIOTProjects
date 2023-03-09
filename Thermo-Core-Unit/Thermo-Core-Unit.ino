int OVERRIDE_STATE = false;
int TEMP_THRESHOLD = 30;

#include "dht.h"
#include "oled.h"
#include "relay.h"
#include "server.h"

String displayMessage = "";

void setRelayControl(){
  if(TEMP_THRESHOLD > GLOBAL_TEMP_VAL){
      switchRelay(0x1100, HIGH);
      switchRelay(0x2200, HIGH);
  }else{
      switchRelay(0x1100, LOW);
      switchRelay(0x2200, LOW);  
  }
}

void setup() {
  initSensor();
  initOLED();
  initNet();
  initServer();
  initRelays();
}

void loop() {
  runServer();
  
  clearScreen();
  displayMessage = "*C: " + String(GLOBAL_TEMP_VAL)+" Th: "+String(TEMP_THRESHOLD);
  displayTopRow("Modular Heating");
  
  displayBottomRow(displayMessage.c_str());
  if(!OVERRIDE_STATE){
    setRelayControl();
  }
  delay(1000);
}
