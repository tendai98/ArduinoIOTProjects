#include "dht.h"
#include "oled.h"
#include "relay.h"
#include "server.h"

int TEMP_THRESHOLD = 20;
String displayMessage = "";

void setRelayControl(){
  if(GLOBAL_TEMP_VAL > TEMP_THRESHOLD){
      switchRelay(0x2200, LOW);
  }else{
      switchRelay(0x2200, HIGH);  
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
  displayMessage = String(GLOBAL_TEMP_VAL) + " *C : " + String(GLOBAL_HUMD_VAL)  + "%";
  displayTopRow("------[Eddy]-------");
  displayBottomRow(displayMessage.c_str());
  
  setRelayControl();
  delay(1000);
}
