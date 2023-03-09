#include <ESP8266WiFi.h>
#include "DHT.h"

#define WIFI_SSID "SensorNET"
#define WIFI_PASSWORD "12345678"

#define HOSTNAME "green-iot-api.herokuapp.com"
#define HTTPS_PORT 443
#define DHTPIN D1 //--> DHT11 sensor output is connected to PIN D1 on NodeMCU   
#define DHTTYPE DHT11 //--> DHT sensor type declaration     

WiFiClientSecure client;
DHT dht(DHTPIN, DHTTYPE);  
//----------------------------------------

//----------------------------------------Variable declaration of temperature and humidity
int t;
String url;

#define ON_Board_LED D4  //--> GPIO2=D4. Defining an On Board LED, used for indicators when the process of connecting to a wifi router

//========================================================================VOID SETUP
void blinkLED(){
  digitalWrite(D4, LOW);
  delay(50);
  digitalWrite(D4, HIGH);
  delay(50);
}

void setup() {
  
  dht.begin(); //--> Starting the DHT11 library

  delay(1000);

  pinMode(ON_Board_LED,OUTPUT); //--> On Board LED port Direction output
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off Led On Board

  //----------------------------------------The process of connecting nodemcu esp8266 to a WiFi router or AP

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    digitalWrite(ON_Board_LED, LOW);
    delay(100);
    digitalWrite(ON_Board_LED, HIGH);
    delay(100);
  }

  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  client.setInsecure(); 
}
//========================================================================

//========================================================================VOID LOOP
void loop() {
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
  
  if (!isnan(t)){
    if (client.connect(HOSTNAME, HTTPS_PORT)) { 
            
            url="/api?temperature="+String(t);
            
            client.print(
                      String("GET ") + url + " HTTP/1.1\r\n" +
                      "Host: " + HOSTNAME + "\r\n" + 
                      "Connection: close\r\n\r\n");  
    }    
  }
  blinkLED();
}
