#include <OneWire.h>
#include <DallasTemperature.h>

const int oneWireBus = D1;     

OneWire oneWire(oneWireBus);
DallasTemperature sensor(&oneWire);

void setupTemperatureSensor() {
  sensor.begin();
}

int getTempValue() {
  sensor.requestTemperatures(); 
  return sensor.getTempCByIndex(0);
}
