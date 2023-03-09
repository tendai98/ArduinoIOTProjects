
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#define DELAY 1000

PulseOximeter pox;

float heartRate = 0;
float oxygen = 0;
int  lastReportTimeStamp = 0;

void initPox()
{
    while(!pox.begin()) {
        Serial.println("[!] POX: NOT READY");  
    }

    Serial.println("[+] POX: READY");
    delay(1000);
}

float getHeartRate(){
  return heartRate;
}

float getO2(){
  return oxygen;
}

void updatePox(){
    pox.update();
    if (millis() - lastReportTimeStamp > DELAY) {
        heartRate = pox.getHeartRate();
        oxygen = pox.getSpO2();
        lastReportTimeStamp = millis();
        Serial.printf("HeartRate: %f , 02: %f\n", getHeartRate(), getO2()); 
    }
}
