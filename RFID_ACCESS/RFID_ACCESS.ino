#include "rfid.h"
#include "servo.h"

#define VISITOR_TAG_1 0xFFFF83E3  // Blue tag (with access)

void rfidAccessMode(){
  
  int id = -1;  // Setup id value to -1
  while(true){
    id = readCard();
    if(id == VISITOR_TAG_1){ // Compare if we got the right ID
      openMode(); // OPEN BOOM GATE (run servo to 0 degrees)
      delay(5000); // Keep the gate opena u n for 5 seconds
      closeMode(); // CLOSE BOOM GATE (run server to 180 degress)
      break;
    }
  }

  delay(1000); // sleep for 1 second
  
}


void setup() {
    initServo(); // Initialize the servo motor
    initRFID();  // Initialize the RFID 
    closeMode(); // Close the boom gate
}

void loop() {
    rfidAccessMode(); // run the RFID access
}
