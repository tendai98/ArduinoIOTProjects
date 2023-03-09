#define BUZZER 14

void startBuzzer(){
  pinMode(BUZZER, OUTPUT);
}

void driveBuzzer(int d){
  digitalWrite(BUZZER, HIGH);
  delay(d);
  digitalWrite(BUZZER, LOW);
  delay(d);
}
