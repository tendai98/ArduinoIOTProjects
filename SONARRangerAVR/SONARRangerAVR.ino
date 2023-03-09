#include "sonar.h"

#define LED_1 2
#define LED_2 4
#define LED_3 7

int range = 0;

void driveLEDS(int range){
  if(range >= 0 & range < 50){
      digitalWrite(LED_1, HIGH);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, LOW);
  }else if(range >= 50 & range < 75){
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, HIGH);
      digitalWrite(LED_3, LOW);    
  }else if(range >= 75 & range < 100){
      digitalWrite(LED_1, LOW);
      digitalWrite(LED_2, LOW);
      digitalWrite(LED_3, HIGH);    
  }
}

void setup(){
  Serial.begin(9600);
  startSonar();
  
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
}

void loop(){
  range = getDistance();
  Serial.print("Range: ");
  Serial.print(range);
  Serial.println(" cm");  
  driveLEDS(range);
  delay(250);
}
