#define FLOWRATE_GPIO D1

int flow = 0;

ICACHE_RAM_ATTR  void countPulse(){
  flow++;
}

void initFlowRateSensor(){
  attachInterrupt(digitalPinToInterrupt(D1), countPulse, RISING);
}

float readFlowRateSensor(){
  float flowRate = flow * 60.0 / 7.5;
  flow = 0;
  return flowRate;
}
