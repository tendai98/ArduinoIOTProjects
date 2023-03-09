void initControls(){
  pinMode(D5, INPUT_PULLUP);
  pinMode(D4, OUTPUT);
  digitalWrite(D4, HIGH);
}

int getButton(){
  int state = digitalRead(D5);
  if(state){
    digitalWrite(D4, LOW);
  }else{
    digitalWrite(D4, HIGH);
  }

  return state;
}
