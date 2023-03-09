#define REED_GPIO 19

void initializeReedSensor(){
  pinMode(REED_GPIO, INPUT);
}

int getReedSensorState(){
  return digitalRead(REED_GPIO);
}
