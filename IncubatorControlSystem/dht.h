#include <DHT.h>
#include <DHT_U.h>

#define DHT_PIN 2

DHT_Unified dht(DHT_PIN, DHT11);
sensors_event_t data;

float GLOBAL_TEMP = 0.0;
float GLOBAL_HMD = 0.0;
float GLOBAL_TEMP_OFFSET = 0.0;

float getHumidity(){
  dht.humidity().getEvent(&data);
  return data.relative_humidity;
}

float getTemperature(){
  dht.temperature().getEvent(&data);
  return data.temperature + GLOBAL_TEMP_OFFSET;
}

void getSensorData(){
  GLOBAL_HMD = getHumidity();
  GLOBAL_TEMP = getTemperature();
}

void initDHT(){
  dht.begin();
}
