#include <NewPing.h>
#include <Servo.h>
#define TRIGGER_PIN  23
#define ECHO_PIN     22
#define SERVO_PIN    15
#define MAX_DISTANCE 1000

int distance;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
Servo RadarServo; 

void setup() { 
  Serial.begin(115200);
  RadarServo.attach(SERVO_PIN); // Defines on which pin is the servo motor attached
  delay(3000);
}
void loop() {
  // rotates the servo motor from 15 to 165 degrees
  for(int i=0;i<=180;i++){  
    RadarServo.write(i);
    delay(50);
    distance = sonar.ping_cm();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree

 for(int j=0;j<100;j+=25){
      if(i==180 && j>0){
        break;
      }
      Serial.print(i); // Sends the current degree into the Serial Port
      Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
      Serial.print(j); // Sends the current degree into the Serial Port
      Serial.print("*");
      Serial.print(1); // Sends the distance value into the Serial Port
      Serial.print("/"); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
      Serial.print(distance); // Sends the distance value into the Serial Port
      Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
    }
  
  }


  
  // Repeats the previous lines from 165 to 15 degrees
  for(int i=180;i>=0;i--){  
  RadarServo.write(i);
  delay(50);
  distance = sonar.ping_cm();
  for(int j=75;j>=0;j-=25){
if(i==180 &&  (j==75 ||j==50 ||j==25)){
  continue;
}
 Serial.print(i); // Sends the current degree into the Serial Port
  Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(j); // Sends the current degree into the Serial Port
  Serial.print("*");
  Serial.print(-1); // Sends the distance value into the Serial Port
  Serial.print("/"); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  Serial.print(distance); // Sends the distance value into the Serial Port
  Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
  }
  }
}
