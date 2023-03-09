#include "const.h"
#include "wifi.h"
#include "gps.h"
#include "client.h"
#include "acclerometer.h"
#include "ir.h"

String data;
char buff[90];

void setup(){
  startWiFi(NET_SSID, NET_PASS);
  initGPS(DEFAULT_BITRATE);
  initAccelerometer();
  initIRSensor();
}

void loop(){
  getAccelerationData();
  getLocationData();
  
  data = "/api";
  data += "?lon="+String(flon);
  data += "&lat="+String(flat);
  data += "&x="+String(x);
  data += "&y="+String(y);
  data += "&z="+String(z);
  data += "&ir="+String(getIRSensorState());
  data += "&id="+String(TRACKER_NODE_ID);

  data.toCharArray(buff, data.length());
  httpGet(HOST, buff);
  delay(10);
}
