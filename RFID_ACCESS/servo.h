#include <Servo.h>

#define SERVO_PIN 8
Servo servo;

void initServo(){
  servo.attach(SERVO_PIN);
}

void closeMode(){
  servo.write(180);
}

void openMode(){
  servo.write(0);
}
