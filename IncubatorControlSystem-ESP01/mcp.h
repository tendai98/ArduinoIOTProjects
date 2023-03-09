#include <EEPROM.h>

#define FORWARD_ROTATION        2
#define REVERSE_ROTATION        3 
#define TEMP1_ADDRESS_OFFSET    0
#define TEMP2_ADDRESS_OFFSET    4
#define ROT_ADDRESS_OFFSET      8
#define TEMP_OFFSET_ADDRESS     12
#define SLEEP_TIME_ADDRESS      16

float GLOBAL_TEMP_CONTROL1 = 0;
float GLOBAL_TEMP_CONTROL2 = 0;
float GLOBAL_TEMP_OFFSET = 0;
int GLOBAL_ROT_CONTROL = 0;
int GLOBAL_ROT_SLEEP_TIMER = 0;

short state = 0, lastState = 0, counter = 0, lastValue = 0;

void saveParameters(float temp1, float temp2, int rotationTimer, float tempOffset, int rotorSleepTimer){
  EEPROM.put(TEMP1_ADDRESS_OFFSET, temp1);
  EEPROM.put(TEMP2_ADDRESS_OFFSET, temp2);
  EEPROM.put(ROT_ADDRESS_OFFSET, rotationTimer);
  EEPROM.put(TEMP_OFFSET_ADDRESS, tempOffset);
  EEPROM.put(SLEEP_TIME_ADDRESS, rotorSleepTimer);
  
  EEPROM.commit();
  GLOBAL_TEMP_CONTROL1 = temp1;
  GLOBAL_TEMP_CONTROL2 = temp2;
  GLOBAL_TEMP_OFFSET = tempOffset;
  GLOBAL_ROT_CONTROL = rotationTimer;
  GLOBAL_ROT_SLEEP_TIMER = rotorSleepTimer;
}

void loadParameters(){
  EEPROM.get(TEMP1_ADDRESS_OFFSET, GLOBAL_TEMP_CONTROL1);
  EEPROM.get(TEMP2_ADDRESS_OFFSET, GLOBAL_TEMP_CONTROL2);
  EEPROM.get(ROT_ADDRESS_OFFSET, GLOBAL_ROT_CONTROL);
  EEPROM.get(TEMP_OFFSET_ADDRESS, GLOBAL_TEMP_OFFSET);
  EEPROM.get(SLEEP_TIME_ADDRESS, GLOBAL_ROT_SLEEP_TIMER);
}

void initMCP(){
  EEPROM.begin(20);
  loadParameters();
}

/////////////////////// [Rotation Control] /////////////////////

int getState(int state){
  switch(state){
      case REVERSE_ROTATION:
        counter--;
        return state;

      case FORWARD_ROTATION:
        counter++;
        return state;

      default:
        return state;
   }
}

int timer1 = 0;
int timer2 = 0;
int timer3 = 0;
bool enableTimer3 = false;

void computeState(){
  if(millis() - timer1 >= GLOBAL_ROT_CONTROL){
    timer1 = millis();
    state = ((counter >= 0) && !(counter > GLOBAL_ROT_CONTROL)) ? getState(REVERSE_ROTATION) : getState(FORWARD_ROTATION); 
  }
}


void controlRelay(){
   switch(state){
      case FORWARD_ROTATION:
         if(millis() - timer2 >= GLOBAL_ROT_SLEEP_TIMER){
            if (!enableTimer3){
               timer3 = millis();
               enableTimer3 = true;
            }
            if(millis() - timer3 >= GLOBAL_ROT_CONTROL){
              timer2 = millis();
              timer3 = millis();
              enableTimer3 = false;
              setRelayState(ROT_RELAY, LOW);
            }else{
              setRelayState(ROT_RELAY, HIGH);              
            }
         }
         break;

   }
}

/////////////////////// [Rotation Control] /////////////////////

void runMCP(){
   computeState();
   controlRelay();
}
