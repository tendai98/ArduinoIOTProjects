#define TEMP_CONTROL_RELAY 4
#define ROT_CONTROL_RELAY 5
#define MAX_CONTROLS 2
#define TEMP_RELAY 0
#define ROT_RELAY 1

int relays[MAX_CONTROLS] = {TEMP_CONTROL_RELAY, ROT_CONTROL_RELAY};
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
