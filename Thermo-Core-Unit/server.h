#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

String data="";

void getSystemState(){
  server.send(200, "text/plain", data);  
}

void enableSystemOverride(){
  if(OVERRIDE_STATE){
    OVERRIDE_STATE = false;  
  }else{
    OVERRIDE_STATE = true;
  }

  server.send(200, "text/plain", String(OVERRIDE_STATE));
}

void controlFan(){
  if(FAN_RELAY_STATE){
    FAN_RELAY_STATE = false;
    switchRelay(0x1100, FAN_RELAY_STATE);   
  }else{
    FAN_RELAY_STATE = true;
    switchRelay(0x1100, FAN_RELAY_STATE);       
  }
  server.send(200, "text/plain", String(FAN_RELAY_STATE));
}

void controlThermoCore(){
  if(HEATER_RELAY_STATE){
    HEATER_RELAY_STATE = false;
    switchRelay(0x2200, HEATER_RELAY_STATE);   
  }else{
    HEATER_RELAY_STATE = true;
    switchRelay(0x2200, HEATER_RELAY_STATE);       
  }  
  server.send(200, "text/plain", String(HEATER_RELAY_STATE));
}

void setTempThreshold(){
  TEMP_THRESHOLD = server.arg(0).toInt();
  server.send(200, "text/plain", String(TEMP_THRESHOLD));  
}

void resetSystem(){
  server.send(200, "text/plain", "Reset"); 
  delay(3000);
  ESP.reset();
}

void initNet(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP("Temperature-Control","qwertyuiop");
}

void initServer(){
  server.on("/threshold", setTempThreshold);
  server.on("/state", getSystemState);
  server.on("/override", enableSystemOverride);
  server.on("/fan", controlFan);
  server.on("/core", controlThermoCore);
  server.on("/reset", resetSystem);
  server.begin();
}

void runServer(){
  GLOBAL_TEMP_VAL = getTemperature();
  GLOBAL_HUMD_VAL = getHumidity();
  
  data = String(GLOBAL_TEMP_VAL) + ":" + String(GLOBAL_HUMD_VAL) + ":" + String(HEATER_RELAY_STATE); 
  data += ":" + String(HEATER_RELAY_STATE) + ":" + String(FAN_RELAY_STATE) +":" + String(TEMP_THRESHOLD);
  server.handleClient();
  delay(100);
}
