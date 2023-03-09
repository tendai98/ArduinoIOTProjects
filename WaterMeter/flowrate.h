#define FLOWRATE_GPIO D1

float flowRate = 0;
int flow = 0;
int averageWaterFlow = 0;
int interval1 = 0, interval2 = 0;

IRAM_ATTR  void countPulse(){
  flow++;
}

void initFlowRateSensor(){
  attachInterrupt(digitalPinToInterrupt(FLOWRATE_GPIO), countPulse, RISING);
}

float readFlowRateSensor(){
  if((millis() - interval1) > 1000){
    flowRate = ((1000.0 / (millis() - interval1)) * flow) / 7.5;
    interval1 = millis();
    flow = 0;
  }
  return flowRate;
}

void  calculateAverageFlow(){
  if((millis() - interval2) >= (1000*60)){
    interval2 = millis();
    averageWaterFlow += flowRate;
  }
}
