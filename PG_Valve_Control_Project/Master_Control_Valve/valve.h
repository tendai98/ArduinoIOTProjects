#define VALVE_GPIO        D0
#define LED_GPIO          D4
#define VALVE_OFF         HIGH
#define VALVE_ON          LOW

int masterValveState = 0;

void initValveControl(){
  pinMode(VALVE_GPIO, OUTPUT);
  pinMode(LED_GPIO, OUTPUT);
  digitalWrite(VALVE_GPIO, VALVE_OFF);
  digitalWrite(VALVE_GPIO, VALVE_OFF);
}

void shutDownValve(){
  digitalWrite(VALVE_GPIO, VALVE_OFF);
  digitalWrite(VALVE_GPIO, VALVE_OFF);  
}

void openValve(){
  digitalWrite(VALVE_GPIO, VALVE_ON);
  digitalWrite(VALVE_GPIO, VALVE_ON);  
}


void executeValveControl(int state){
  masterValveState = state;
  digitalWrite(VALVE_GPIO, state);
}
