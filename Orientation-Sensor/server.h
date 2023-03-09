#include <ESP8266WebServer.h>
#include "mpu6050.h"

ESP8266WebServer web(80);
String data = "";

void sendSensorData(){
  data += String(GYRO_X)+",";
  data += String(GYRO_Y)+",";
  data += String(GYRO_Z)+",";

  data += String(AXXL_X)+",";
  data += String(AXXL_Y)+",";
  data += String(AXXL_Z)+",";
  data += String(TEMP_C)+",";  
  web.send(200, "text/plain", data);
  data = "";
}


void initServer(){
  initMPU6050();
  web.on("/data", sendSensorData);
  web.begin(); 
}

void handleRequest(){
  getSensorData();
  web.handleClient();
}
