#define LED_PIN   D4

#define TRIG_GPIO D0
#define ECHO_GPIO D1

void hardware_up(){
  pinMode(LED_PIN, OUTPUT);
  pinMode(TRIG_GPIO, OUTPUT);
  pinMode(ECHO_GPIO, INPUT);
}

int readValue(){
  digitalWrite(TRIG_GPIO, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_GPIO, HIGH);
  delayMicroseconds(2);
  digitalWrite(TRIG_GPIO, LOW);
  long duration = pulseIn(ECHO_GPIO, HIGH);
  return duration;
}

void controlLed(int state){
     digitalWrite(LED_PIN, state);
}
