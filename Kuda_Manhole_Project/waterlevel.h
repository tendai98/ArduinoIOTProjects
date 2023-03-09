#define WATER_LEVEL_SENSOR_GPIO 35
#define MAX_ADC_REF 4096
 
int getWaterLevel(){
  return analogRead(WATER_LEVEL_SENSOR_GPIO);
}
