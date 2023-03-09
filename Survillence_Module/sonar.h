const int pingPin = 2; // Trigger Pin of Ultrasonic Sensor
const int echoPin = 14; // Echo Pin of Ultrasonic Sensor

// Initialize the SONAR sensors
void startSonar() {
   pinMode(pingPin, OUTPUT);
   pinMode(echoPin, INPUT);
}

long centimeters(long microseconds) {
   return microseconds / 29 / 2;
}

// Drive the sonar sensor to get signals and calculate range value
int getDistance() {
   digitalWrite(pingPin, LOW); // Set the pin Pin to low state
   delayMicroseconds(2);        // Hold for 2 microseconds
   digitalWrite(pingPin, HIGH); // Set the pin Pin to high state
   delayMicroseconds(10); // Hold for 10 microseconds
   digitalWrite(pingPin, LOW); // Set the pin Pin to low state
   long duration = pulseIn(echoPin, HIGH); // Calculate the pulses from the echoPin
   return centimeters(duration); // Calculate the distance
}
