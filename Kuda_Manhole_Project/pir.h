#define PIR_GPIO 21

void initializePIRSensor(){
  pinMode(PIR_GPIO, INPUT);
}

int getPIRState(){
  return digitalRead(PIR_GPIO);
}
