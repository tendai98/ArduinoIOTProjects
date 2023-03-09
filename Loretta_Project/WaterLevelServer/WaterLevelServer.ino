#include "wifi.h"
#include "http.h"
#define RELAY_PIN D0


void blinkLED(){
  digitalWrite(D4, LOW);
  delay(25);
  digitalWrite(D4, HIGH);
  delay(25);
}


void driveRelay(int state){
  digitalWrite(RELAY_PIN, state);
}


void setup() {
    pinMode(D4, OUTPUT);
    pinMode(D0, OUTPUT);
    initWiFi();
    initHttp();
}

void loop() {
   int value = analogRead(ANALOG_SENSOR_PIN);  // Ready analog pin
  
  if(512 > value){
    driveRelay(HIGH);
  }else{
    driveRelay(LOW);
  }
  
  handleClients();
  blinkLED();
}
