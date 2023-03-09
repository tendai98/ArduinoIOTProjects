#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

String data="";

void getSystemState(){
  server.send(200, "text/plain", data);  
}

void resetSystem(){
  server.send(200, "text/plain", "Reset"); 
  delay(3000);
  ESP.reset();
}

void initNet(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Cooling Unit","01234567");
}

void initServer(){
  server.on("/state", getSystemState);
  server.on("/reset", resetSystem);
  server.begin();
}

void runServer(){
  GLOBAL_TEMP_VAL = getTemperature();
  GLOBAL_HUMD_VAL = getHumidity();
  data = String(GLOBAL_TEMP_VAL) + ":" + String(GLOBAL_HUMD_VAL) + ":" + String(HEATER_RELAY_STATE); 
  
  server.handleClient();
  delay(100);
}
