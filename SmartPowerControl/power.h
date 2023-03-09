#define RELAY_CONTROL_PIN D1
#define SENSOR_INPUT_PIN A0
#define RELAY_ON_OPCODE 0x11AA
#define RELAY_OFF_OPCODE 0x22BB
#define RESET_OPCODE 0x33CC
#define DC_CURRENT_MODE 0x44DD
#define AC_CURRENT_MODE 0x55EE

#include "ACS712.h"

ACS712 ACS(SENSOR_INPUT_PIN, 5.0,1023,185);
boolean acsOnline = false;
unsigned int deviceMode = AC_CURRENT_MODE;

void initACS(){
  pinMode(RELAY_CONTROL_PIN,OUTPUT);
  digitalWrite(RELAY_CONTROL_PIN,LOW);
  ACS.autoMidPoint();
  acsOnline = true;
}

double currentReading(){
    double value = 0;
    
    switch(deviceMode){
        
        case AC_CURRENT_MODE:
              value = ACS.mA_AC();
              return value;
              
        case DC_CURRENT_MODE:
              value = ACS.mA_DC();
              value *= (((int) value) > 0) ;
              Serial.println((((int) value) > 0));
              return value;
              
        default:
              value = ACS.mA_AC();
              return value;
              
    }
  
}

void controlRelayState(boolean state){
  if(acsOnline){
    if(state){
      digitalWrite(RELAY_CONTROL_PIN,HIGH);
    }else{
      digitalWrite(RELAY_CONTROL_PIN,LOW);
    }
  }
}

void systemControl(unsigned int opcode){

    switch(opcode){
      
        case RELAY_ON_OPCODE:
            controlRelayState(true);
            break;

        case RELAY_OFF_OPCODE:
            controlRelayState(false);
            break;

        case RESET_OPCODE:
            ESP.reset();

        case AC_CURRENT_MODE:
              deviceMode = AC_CURRENT_MODE;
              break;
              
        case DC_CURRENT_MODE:
              deviceMode = DC_CURRENT_MODE;
              break;
    }
  
}
