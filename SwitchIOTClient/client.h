#define GATEWAY_VM_URI "http://192.168.4.2:8081/state"

#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

HTTPClient http;
WiFiClient client;

int errorCode = 0;
int state = 0;

void getState(char * url){
  
  http.begin(client, url);  // begin HTTP GET using given URL
  errorCode = http.GET(); // Send HTTP GET
  
  if(errorCode > 0){
     state = http.getString().toInt();  // Set the value with unit     
  }

  http.end();
}
