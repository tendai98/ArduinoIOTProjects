#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer web(8080);
int state = 0;
const int RELAY_PIN_0 =  0;
const int RELAY_PIN_1  = 2;
char AP_NAME[] = "SolarControlSystem";
char AP_PSK[] = "1234567890";

void setRelayState(){
  state = web.arg(0).toInt();
  digitalWrite(RELAY_PIN_0, state);  
  digitalWrite(RELAY_PIN_1, state);
  web.send(200, "text/plain", state == 1 ? "ON" : "OFF");
}

void initRelayGPIO(){
  pinMode(RELAY_PIN_0, OUTPUT);
  pinMode(RELAY_PIN_1, OUTPUT);
  digitalWrite(RELAY_PIN_0, LOW);  
  digitalWrite(RELAY_PIN_1, LOW);
}

void initWiFiNet(){
  //delay(5000); // Will position the relay with desired IP address
  initRelayGPIO();
  WiFi.mode(WIFI_STA);
  WiFi.begin(AP_NAME, AP_PSK);
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
  }
}

void setup(){
  initWiFiNet();
  web.on("/state", setRelayState);
  web.begin();  
}

void loop(){
  web.handleClient();
}
