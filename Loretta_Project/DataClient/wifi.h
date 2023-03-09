#define BLINK_LED             D4
#define TIME_DELAY            100

#include <ESP8266WiFi.h>

void connectWiFiClient(const char * ssid, const char * password){

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password); // Run WIFI in client mode
  pinMode(BLINK_LED, OUTPUT);     // Control built-in LED using D4
  
  while (WiFi.status() != WL_CONNECTED){  // Blink LED while waiting to connect
    digitalWrite(BLINK_LED, HIGH);
    delay(TIME_DELAY);
    digitalWrite(BLINK_LED, LOW);
    delay(TIME_DELAY);
  }

  digitalWrite(BLINK_LED, HIGH);
  
}

void startWiFiHotSpot(const char * ssid, char * password){
  
  WiFi.softAP(ssid, password);     // Run WIFI in AP mode
  pinMode(BLINK_LED, OUTPUT);     // Control built-in LED using D4
  
}
