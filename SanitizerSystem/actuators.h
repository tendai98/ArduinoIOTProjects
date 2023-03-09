// ======================= [Actuator Control GPIO] ========================== 
#define VALVE_ID 0x0
#define LIGHT_ID 0x1
#define PUMP_ID  0x2

#define VALVE    0x5
#define LIGHT    0x4
#define PUMP     0x3
#define ACTUATORS 3
// ======================= [Actuator Control GPIO] ==========================

const int actuators[ACTUATORS] = {VALVE, LIGHT, PUMP};

void actuate(int actuatorIndex, int state){
   digitalWrite(actuators[actuatorIndex], state);
}


void initializeActuators(){
   for(int i=0; ACTUATORS>i; i++){
      pinMode(actuators[i], OUTPUT);
      digitalWrite(actuators[i], HIGH);
   }
}
