#include <ESP8266WiFi.h>
#define FLASH_LED_GPIO D4

void startWiFi(char * ssid, char * password){
  WiFi.hostname("Sensor-0");
  WiFi.mode(WIFI_STA);
  pinMode(FLASH_LED_GPIO, OUTPUT);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED){
    digitalWrite(FLASH_LED_GPIO, LOW);
    delay(100);
    digitalWrite(FLASH_LED_GPIO, HIGH);
    delay(100);
  }

  digitalWrite(FLASH_LED_GPIO, HIGH);
}
