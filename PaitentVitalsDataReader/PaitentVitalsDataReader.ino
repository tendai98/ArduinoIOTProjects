#include "max30100.h"

#define DEFAULT_BAUDRATE  115200

void setup() {
  initMAX30100Sensor();
  Serial.begin(DEFAULT_BAUDRATE);
}

void loop() {
  sensorUpdate();
  if(validateData()){
    Serial.printf("%.2f,%.2f\n", GLOBAL_BPM, GLOBAL_SPO2);
  }
  delay(100);
}
