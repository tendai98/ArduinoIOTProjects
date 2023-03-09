#include "wifi.h"
#include "server.h"

void setup(){
  initWiFi();
  initServer();
  //Serial.begin(115200);  
}

void loop(){
    handleRequest();
    //Serial.printf("gX:%f  gY:%f  gZ:%f\n", GYRO_X, GYRO_Y, GYRO_Z);
    //Serial.printf("aX:%f  aY:%f  aZ:%f\n", AXXL_X, AXXL_Y, AXXL_Z);
    //Serial.printf("Temp *C: %f\n", TEMP_C);
    blinkLed(50);
}
