const int pingPin1 = D0; // Trigger Pin of Ultrasonic Sensor
const int echoPin1 = D1; // Echo Pin of Ultrasonic Sensor

const int pingPin2 = D2; // Trigger Pin of Ultrasonic Sensor
const int echoPin2 = D3; // Echo Pin of Ultrasonic Sensor

const int pingPin3 = D5; // Trigger Pin of Ultrasonic Sensor
const int echoPin3 = D6; // Echo Pin of Ultrasonic Sensor

const int pingPin4 = D7; // Trigger Pin of Ultrasonic Sensor
const int echoPin4 = D8; // Echo Pin of Ultrasonic Sensor

long centimeters(long microseconds) {
   return microseconds / 29 / 2;
}

void initSonar1() {
   pinMode(pingPin1, OUTPUT);
   pinMode(echoPin1, INPUT);
}

void initSonar2() {
   pinMode(pingPin2, OUTPUT);
   pinMode(echoPin2, INPUT);
}

void initSonar3() {
   pinMode(pingPin3, OUTPUT);
   pinMode(echoPin3, INPUT);
}

void initSonar4() {
   pinMode(pingPin4, OUTPUT);
   pinMode(echoPin4, INPUT);
}

int getSonar1Distance() {
   digitalWrite(pingPin1, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin1, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin1, LOW);
   long duration = pulseIn(echoPin1, HIGH);
   return centimeters(duration);
}

int getSonar2Distance() {
   digitalWrite(pingPin2, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin2, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin2, LOW);
   long duration = pulseIn(echoPin2, HIGH);
   return centimeters(duration);
}

int getSonar3Distance() {
   digitalWrite(pingPin3, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin3, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin3, LOW);
   long duration = pulseIn(echoPin3, HIGH);
   return centimeters(duration);
}

int getSonar4Distance() {
   digitalWrite(pingPin4, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin4, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin4, LOW);
   long duration = pulseIn(echoPin4, HIGH);
   return centimeters(duration);
}
