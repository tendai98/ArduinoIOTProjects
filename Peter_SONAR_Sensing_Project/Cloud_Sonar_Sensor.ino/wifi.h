#include <ESP8266WiFi.h>
#define BLINK_LED D4

void blink(){
    digitalWrite(BLINK_LED, HIGH);
    delay(100);
    digitalWrite(BLINK_LED, LOW);
}

void wifi_up(char * ssid, char * passwd, int connectDelay){
    
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,passwd);
  pinMode(BLINK_LED, OUTPUT);
  
  while (WiFi.status() != WL_CONNECTED){
    delay(connectDelay);
    blink();
  }

  pinMode(BLINK_LED, INPUT);
}
