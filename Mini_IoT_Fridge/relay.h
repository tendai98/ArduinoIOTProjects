#define FAN_RELAY D5
#define HEATER_RELAY D7

int FAN_RELAY_STATE;
int HEATER_RELAY_STATE;

void initRelays(){
  pinMode(HEATER_RELAY, OUTPUT);
  digitalWrite(HEATER_RELAY, LOW);
  HEATER_RELAY_STATE = LOW;
}

void switchRelay(int target, int setState){
  switch(target){
    case 0x1100:
      digitalWrite(FAN_RELAY, setState); 
      FAN_RELAY_STATE = setState;
      break;
      
    case 0x2200:
      digitalWrite(HEATER_RELAY, setState); 
      HEATER_RELAY_STATE = setState;
      break;
  }
}
