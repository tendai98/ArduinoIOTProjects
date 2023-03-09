#include "net.h"
#include "sensors.h"
#include "display.h"
#include "server.h"

char buff[64];
String data = "";

void setup() {
  initOLED();
  setString("[ MONITOR ONLINE ]", 16, 16);
  initAP();
  initHttp();
  delay(2000);
  clearScreenBuffer();
}

void loop() {
  handleClients();
  readKeyCode();
  
  if(KEY_CODE == 0 && newMessage == 0){
    data = String("BPM: ")+String(getBPM());
    data.toCharArray(buff, 64);
    setString(buff, 8, 8);
    delay(1);    
    data = String("O2: ")+String(getO2());
    data.toCharArray(buff, 64);
    setString(buff, 8, 16);
    delay(200);
    clearScreenBuffer();
  }else if(KEY_CODE > 0){
    clearScreenBuffer();
    newMessage = 0;    
  }
  
}
