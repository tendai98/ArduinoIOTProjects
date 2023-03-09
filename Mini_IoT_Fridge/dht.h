#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define GPIO_PIN D3

int GLOBAL_TEMP_VAL = 0;
int GLOBAL_HUMD_VAL = 0;

DHT_Unified dht(GPIO_PIN, DHT11);
sensors_event_t event;

void initSensor(){
  dht.begin();
}

int getTemperature(){
  dht.temperature().getEvent(&event);
  return event.temperature;  
}


int getHumidity(){
  dht.humidity().getEvent(&event);  
  return event.relative_humidity;
}
