#include <Servo.h>
#define SERVO_PIN 15

Servo lockServo;

void initServo(){
  lockServo.attach(SERVO_PIN);
  lockServo.write(0);  
}

void driveServo(int angle){
  lockServo.write(angle);
}
