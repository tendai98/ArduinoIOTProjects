#define BUZZER_GPIO D2

void initAlarm(){
  pinMode(BUZZER_GPIO, OUTPUT);
}

int triggerAlarm(){
  digitalWrite(BUZZER_GPIO, HIGH);
}
