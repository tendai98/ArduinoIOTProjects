#define LOCK_GPIO        D3
#define LED_GPIO         D4
#define UNLOCK_OFF       LOW
#define LOCK_ON          HIGH

int doorLockState = 1;

void initLockControl(){
  pinMode(LOCK_GPIO, OUTPUT);
  pinMode(LED_GPIO, OUTPUT);
  digitalWrite(LOCK_GPIO, UNLOCK_OFF);
}

void lock(){
  doorLockState = 1;
  digitalWrite(LOCK_GPIO, UNLOCK_OFF);  
}

void unlock(){
  doorLockState = 0;
  digitalWrite(LOCK_GPIO, LOCK_ON);
  delay(2000);
  digitalWrite(LOCK_GPIO, UNLOCK_OFF);  
}
