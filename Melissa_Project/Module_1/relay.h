
#define RELAY_GPIO       D2
#define LED_GPIO         D4

void initRelayControl(){
  pinMode(RELAY_GPIO, OUTPUT);
  pinMode(LED_GPIO, OUTPUT);
  digitalWrite(LED_GPIO, HIGH);  
  digitalWrite(RELAY_GPIO, LOW);
}

void activate(){
  digitalWrite(LED_GPIO, LOW);  
  digitalWrite(RELAY_GPIO, HIGH);
}

void deactivate(){
  digitalWrite(LED_GPIO, HIGH);  
  digitalWrite(RELAY_GPIO, LOW);
}
