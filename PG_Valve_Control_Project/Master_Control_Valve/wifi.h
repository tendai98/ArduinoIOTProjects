#include <ESP8266WiFi.h>

#define ap_name "valve-control"
#define ap_pass "control-sys-90"

void initNetwork(){
 WiFi.mode(WIFI_STA);
  WiFi.softAP(ap_name, ap_pass);
  Serial.begin(9600);
  
  /*pinMode(D4, OUTPUT);
  while(WiFi.status() != WL_CONNECTED){
    digitalWrite(D4, HIGH);
    delay(100);
    digitalWrite(D4, LOW);
    delay(100);
    Serial.print("-");
  }*/

  Serial.println("Connected");
  digitalWrite(D4, HIGH);
}
