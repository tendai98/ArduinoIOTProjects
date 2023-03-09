#include <ESP8266WiFi.h>

#define WIFI_DELAY 100
#define HTTPS_PORT 443
#define LIMIT 1037
#define LED_PIN D4

#define HOSTNAME "iot-system-0.herokuapp.com"
#define WIFI_PSK "Qwertyuiop@123456789"
#define WIFI_SSID ".."

WiFiClientSecure client;
String url;

const int pingPin = D0; // Trigger Pin of Ultrasonic Sensor
const int echoPin = D1; // Echo Pin of Ultrasonic Sensor

long centimeters(long microseconds) {
   return microseconds / 29 / 2;
}

long distance() {
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(2);
   digitalWrite(pingPin, LOW);
   long duration = pulseIn(echoPin, HIGH);
   return centimeters(duration);
}

  
void setup() {
  
 pinMode(pingPin, OUTPUT);
 pinMode(echoPin, INPUT);
  WiFi.begin(WIFI_SSID, WIFI_PSK);
  pinMode(LED_PIN, OUTPUT);
  
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_PIN, HIGH);
    delay(WIFI_DELAY);
    digitalWrite(LED_PIN, LOW);
    delay(WIFI_DELAY);
  }

  client.setInsecure(); 
  
}

void loop() {


  if (client.connect(HOSTNAME, HTTPS_PORT)) { 
  
      url="/api";
      url += "?value="+String(distance());
      
      client.print(
                String("GET ") + url + " HTTP/1.1\r\n" +
                "Host: " + HOSTNAME + "\r\n" + 
                "Connection: close\r\n\r\n"
      );  
  }
  delay(10);
  
}
