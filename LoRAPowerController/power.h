#define SENSOR_INPUT_PIN A0
#define RESET_OPCODE 0x43
#define DC_CURRENT_MODE 0x44
#define AC_CURRENT_MODE 0x55

#include "ACS712.h"

ACS712 ACS(SENSOR_INPUT_PIN, 5.0, 1023, 185);
boolean acsOnline = false;
unsigned int deviceMode = AC_CURRENT_MODE;

void initACS(){
  ACS.autoMidPoint();
  acsOnline = true;
}

double currentReading(){
    double rawCurrent = 0;
    
    switch(deviceMode){
        
        case AC_CURRENT_MODE:
              rawCurrent = ACS.mA_AC();
              return rawCurrent;
              
        case DC_CURRENT_MODE:
              rawCurrent = ACS.mA_DC();
              rawCurrent *= (((int) rawCurrent) > 0) ;
              return rawCurrent;
              
        default:
              rawCurrent = ACS.mA_AC();
              return rawCurrent;
              
    }
  
}


void systemControl(char opcode){

    switch(opcode){
  
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
