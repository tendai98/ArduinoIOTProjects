const int pingPin = 4; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 2; // Echo Pin of Ultrasonic Sensor

void startSonar() {
   pinMode(pingPin, OUTPUT);
   pinMode(echoPin, INPUT);
}

long centimeters(long microseconds) {
   return microseconds / 29 / 2;
}

int getDistance() {
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   long duration = pulseIn(echoPin, HIGH);
   return centimeters(duration);
}
