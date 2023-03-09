
#include <Servo.h>

#define SERVO_PIN 12
Servo servo;

void initServo(){
  servo.attach(SERVO_PIN);
}

void runLockProc(){
  servo.write(90);
}

void runUnLockProc(){
  servo.write(0);
}
