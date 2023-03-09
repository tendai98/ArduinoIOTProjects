#define RELAY_1_GPIO D0
#define RELAY_2_GPIO D1

#define RELAY_1_ON  0x41
#define RELAY_1_OFF 0x42
#define RELAY_2_ON  0x31
#define RELAY_2_OFF 0x32

bool RELAY_1 = LOW;
bool RELAY_2 = LOW;

void initControlRelays(){
  pinMode(RELAY_1_GPIO, OUTPUT);
  pinMode(RELAY_2_GPIO, OUTPUT);
  digitalWrite(RELAY_1_GPIO, LOW);
  digitalWrite(RELAY_2_GPIO, LOW);
}


void controlRelay(char opcode){
  switch(opcode){
    
    case RELAY_1_ON:
       RELAY_1 = HIGH;
       digitalWrite(RELAY_1_GPIO, HIGH);
       break;

    case RELAY_1_OFF:
       RELAY_1 = LOW;
       digitalWrite(RELAY_1_GPIO, LOW);
       break;

    case RELAY_2_ON:
       RELAY_2 = HIGH;
       digitalWrite(RELAY_2_GPIO, HIGH);
       break;

    case RELAY_2_OFF:
       RELAY_2_OFF;
       RELAY_2 = LOW;
       digitalWrite(RELAY_2_GPIO, LOW);
       break;
  }
    
}
