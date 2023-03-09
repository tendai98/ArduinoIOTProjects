#define BUZZER_GPIO 32

void initializeBuzzer(){
  pinMode(BUZZER_GPIO, OUTPUT);
  digitalWrite(BUZZER_GPIO, LOW);
}

void runBuzzer(int buzzDelay){
  digitalWrite(BUZZER_GPIO, HIGH);
  delay(buzzDelay);
  digitalWrite(BUZZER_GPIO, LOW);
  delay(buzzDelay);
}
