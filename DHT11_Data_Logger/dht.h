#include <DHT.h>
#include <DHT_U.h>

#define DHT_PIN 0


DHT_Unified dht(DHT_PIN, DHT11);
sensors_event_t data;


float GLOBAL_TEMP = 0.0;
float GLOBAL_HMD = 0.0;
char * buff1, buff2;
String msg1, msg2, logData;

float getHumidity(){
  dht.humidity().getEvent(&data);
  return data.relative_humidity;
}

float getTemperature(){
  dht.temperature().getEvent(&data);
  return data.temperature;
}

void getSensorData(){
  GLOBAL_HMD = getHumidity();
  GLOBAL_TEMP = getTemperature();
  logData = String(GLOBAL_TEMP)+","+String(GLOBAL_HMD)+"\n";
}

void initDHT(){
  dht.begin();
}
