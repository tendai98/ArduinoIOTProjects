#define IR_SENSOR_GPIO D0

void setupIRSensor(){
  pinMode(IR_SENSOR_GPIO, INPUT);
}

int getIRSensorState(){
  return digitalRead(IR_SENSOR_GPIO);
}
