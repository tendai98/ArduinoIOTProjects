void initIRSensor(){
  pinMode(D6, INPUT_PULLUP); 
}

int getIRSensorState(){
  return !digitalRead(D6);
}
