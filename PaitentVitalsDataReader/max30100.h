#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS  1000

PulseOximeter pox;

uint32_t tsLastReport = 0;
float GLOBAL_BPM = 0;
float GLOBAL_SPO2 = 0;
int bpm;
int spo2;

void initMAX30100Sensor()
{
    if(!pox.begin()) {
        for(;;);
    }
}

bool validateData(){
  bpm = (int) GLOBAL_BPM;
  spo2 = (int) GLOBAL_SPO2;
  return (bpm > 0 && bpm < 110 && spo2 > 0 && spo2 < 100);
}

void sensorUpdate()
{
    pox.update();
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        GLOBAL_BPM = pox.getHeartRate();
        GLOBAL_SPO2 = pox.getSpO2();
        tsLastReport = millis();
    }
}
