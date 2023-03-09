// ======================= [SONAR Sensor GPIO] ==========================
#define ECHO_GPIO   0xa
#define PING_GPIO   0x9
#define SENSE_PROXIMITY 50
// ======================= [SONAR Sensor GPIO] ==========================

// ======================= [SONAR Sensor Subroutines] ==========================

long getProximity(long epoch){
    return epoch / 29 / 2;
}

long driveSonar(){
  digitalWrite(PING_GPIO, LOW);
  delayMicroseconds(2);
  digitalWrite(PING_GPIO, HIGH);
  delayMicroseconds(10);
  digitalWrite(PING_GPIO, LOW);
  return pulseIn(ECHO_GPIO, HIGH);
}

void initializeSonarSensor(){
  pinMode(ECHO_GPIO, INPUT);
  pinMode(PING_GPIO, LOW);
  digitalWrite(ECHO_GPIO, LOW);  
}

// ======================= [SONAR Sensor Subroutines] ==========================
