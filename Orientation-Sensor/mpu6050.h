#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_MPU6050.h>


Adafruit_MPU6050 mpuDevice;
sensors_event_t axxEvent, gyroEvent, tempEvent;

float GYRO_X = 0, GYRO_Y = 0, GYRO_Z = 0;
float AXXL_X = 0, AXXL_Y = 0, AXXL_Z = 0;
float TEMP_C = 0;

void initMPU6050(){
  if(!mpuDevice.begin()){
    ESP.reset();
  }
  mpuDevice.setAccelerometerRange(MPU6050_RANGE_8_G);
}

void getSensorData(){
  mpuDevice.getEvent(&gyroEvent, &axxEvent, &tempEvent);
  
  GYRO_X = gyroEvent.gyro.x;
  GYRO_Y = gyroEvent.gyro.y;
  GYRO_Z = gyroEvent.gyro.z;

  AXXL_X = axxEvent.acceleration.x;
  AXXL_Y = axxEvent.acceleration.y;
  AXXL_Z = axxEvent.acceleration.z;

  TEMP_C = tempEvent.temperature;
}
