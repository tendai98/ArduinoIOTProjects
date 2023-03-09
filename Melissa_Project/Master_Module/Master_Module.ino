#define GAS_SENSOR_GPIO   D1
#define REED_SENSOR_GPIO  D2
#define TARGET_THRESHOLD 400

void initBus(){
  pinMode(GAS_SENSOR_GPIO, OUTPUT);
  pinMode(REED_SENSOR_GPIO, OUTPUT);
  digitalWrite(GAS_SENSOR_GPIO, LOW);
  digitalWrite(REED_SENSOR_GPIO, LOW);
}

void sendSignals(){
  int reed = digitalRead(D4);
  int gas = TARGET_THRESHOLD > analogRead(A0);
  digitalWrite(GAS_SENSOR_GPIO, gas);
  digitalWrite(REED_SENSOR_GPIO, reed); 
  Serial.printf("%d %d", reed, gas);
  Serial.println();
}

void setup(){
  initBus();
  pinMode(D5, OUTPUT);
  digitalWrite(D5, LOW);
  Serial.begin(9600);
}

void driveLEDS(){
  if(TARGET_THRESHOLD > analogRead(A0)){
    digitalWrite(D5, HIGH);
  }else{
    digitalWrite(D5, LOW);
  }  
}

void loop(){
  driveLEDS();
  sendSignals();
  delay(10);
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
