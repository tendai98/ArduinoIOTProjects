#include "const.h"
#include "wifi.h"
#include "gps.h"
#include "client.h"

#define TRACKER_ID "AET9659"
char bufferData[30];

void setup(){
  startWiFi(NET_SSID, NET_PASS);
  initGPS(DEFAULT_BITRATE);
  Serial.begin(9600);
}

void loop(){
  getLocationData();
  Serial.printf("\n\nLATITUDE: %f\nLONGITUDE: %f\n\n", GLOBAL_GPS_LAT, GLOBAL_GPS_LON);
  
  GLOBAL_DATA = "/api";
  GLOBAL_DATA += "?longitude="+String(GLOBAL_GPS_LON);
  GLOBAL_DATA += "&latitude="+String(GLOBAL_GPS_LAT);
  GLOBAL_DATA += "&speed="+String(GLOBAL_GPS_SPEED);
  GLOBAL_DATA += "&id="+String(TRACKER_ID);
 
  httpGet(HOST);
  delay(10);
  
}
