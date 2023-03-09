#define LED_1   4
#define LED_2   5
#define BUZZER  18
#define DEFAULT_TIMEOUT 100

void initHardware(){
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(BUZZER, LOW);  
}

void driveAlert(){
  for (int count=0; count<3; count++){
    digitalWrite(BUZZER, HIGH);
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    delay(DEFAULT_TIMEOUT);
    digitalWrite(BUZZER, LOW);
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    delay(DEFAULT_TIMEOUT);
  }

  digitalWrite(BUZZER, LOW);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
}
