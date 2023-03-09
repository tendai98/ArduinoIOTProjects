#define SENSOR_GPIO A0
#define ADC_MAX 1024.0
#define MAX_VLT 3.27

float readPhValue(int gpio){
  float volt = 0;
  
  volt = analogRead(gpio) * MAX_VLT / ADC_MAX;
  return 7.0 - (2.5 - volt);
}
