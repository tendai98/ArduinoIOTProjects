#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

float x,y,z;

void initAccelerometer() 
{
  if(!accel.begin()){
    while(1);
  }
  accel.setRange(ADXL345_RANGE_4_G);
}

void getAccelerationData() 
{
  sensors_event_t event; 
  accel.getEvent(&event);

  x = (event.acceleration.x)/9.8;
  y = (event.acceleration.y)/9.8;
  z = (event.acceleration.z)/9.8;
}
