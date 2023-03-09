#define BUTTON_1 D0
#define BUTTON_2 D6
#define BUTTON_3 D5

#define BUTTON_1_CODE 0x000000FF
#define BUTTON_2_CODE 0x0000FF00
#define BUTTON_3_CODE 0x00FF0000

int KEY_CODE = 0;

void pullDownPins(){
  digitalWrite(BUTTON_1, LOW);
  digitalWrite(BUTTON_2, LOW);
  digitalWrite(BUTTON_3, LOW);
}

void initButtons(){
  pinMode(BUTTON_1, INPUT);
  pinMode(BUTTON_2, INPUT);
  pinMode(BUTTON_3, INPUT);
  pullDownPins();
}

int readKeyCode(){
  int key1 = digitalRead(BUTTON_1) * BUTTON_1_CODE;
  int key2 = digitalRead(BUTTON_2) * BUTTON_2_CODE;
  int key3 = digitalRead(BUTTON_3) * BUTTON_3_CODE;
  int state = key1 | key2 | key3;
  KEY_CODE = state;
  pullDownPins();  
  return state;
}
