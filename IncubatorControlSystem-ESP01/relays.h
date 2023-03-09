#define ROT_CONTROL_RELAY_0 0
#define ROT_CONTROL_RELAY_1 2
#define MAX_CONTROLS 2
#define TEMP_RELAY 0
#define ROT_RELAY 1

int relays[MAX_CONTROLS] = {ROT_CONTROL_RELAY_0, ROT_CONTROL_RELAY_1};
int GLOBAL_RELAY_STATES[MAX_CONTROLS];

void initRelays(){
  for(int i = 0;  i<MAX_CONTROLS; i++){
    GLOBAL_RELAY_STATES[i] = LOW;
    pinMode(relays[i], OUTPUT);
    digitalWrite(relays[i], LOW);
  }
}

void setRelayState(int index, int state){
  digitalWrite(relays[index], state);
  GLOBAL_RELAY_STATES[index] = state;
}
