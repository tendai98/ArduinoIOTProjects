#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define GPIO_PIN D2

DHT_Unified dht(GPIO_PIN, DHT11);
sensors_event_t event;

void initSensor(){
  dht.begin();
}

float getTemperature(){
  dht.temperature().getEvent(&event);
  return event.temperature;  
}


float getHumidity(){
  dht.humidity().getEvent(&event);  
  return event.relative_humidity;
}
