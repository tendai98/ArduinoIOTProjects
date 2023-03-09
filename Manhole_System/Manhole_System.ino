#include "net.h"
#include "http.h"

// Hardware Pinout Layout
// Reed Sensors -> D19
// Buzzer       -> D32
// PIR          -> D23
// WaterLevel   -> D15

void runAlertMonitor(){
  if(getPIRState() && getReedSensorState() && isSensorArmed == 1){
    runBuzzer(100);
    sensorTriggered = 1;
  }
}

void setup(){  
  initDataLink();
  initServer();
  //Serial.begin(9600);
}

void loop(){
  //Serial.println(getPIRState());
  runServer();
  blinkLED();
  if(isSensorArmed){
    runAlertMonitor();
  }
}
