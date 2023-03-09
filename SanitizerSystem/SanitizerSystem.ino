#include "actuators.h"
#include "sonar.h"

bool runSanitizationProcedure(){
  actuate(LIGHT_ID, LOW);
  actuate(PUMP_ID, LOW);
  actuate(VALVE_ID, HIGH);
  
  delay(2000);
  actuate(LIGHT_ID, HIGH);
  actuate(PUMP_ID, HIGH);
  actuate(VALVE_ID, LOW);  
  delay(1000);
 
  actuate(VALVE_ID, HIGH); 
  return false;
}

void setup() {
  initializeActuators();
  initializeSonarSensor();
}

void loop() {
  SENSE_PROXIMITY > getProximity(driveSonar()) ? runSanitizationProcedure() : 0;
  delay(150);
}
