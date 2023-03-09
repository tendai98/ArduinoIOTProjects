#include "wifi.h"
#include "client.h"
#include "oled-driver.h"

const char * ssid = "WLS-0";
const char * pass = "1234567890";
char  data[16];

void setup() {
  initOLED();
  printString("Connecting....");
  connectWiFiClient(ssid, pass);
  printString("Connected");
  delay(2000);
}

void loop() {
  httpGet(WATER_LEVEL_SENSOR_URL, data);
  printString(data);
  clearScreenBuffer();  
  delay(50);
}
