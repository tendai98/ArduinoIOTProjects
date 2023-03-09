#include <ESP8266WebServer.h>

#define HTTP_OK_CODE 200
#define HTTP_ERROR_CODE 404
#define OVERRIDE_TIMEOUT 60000
#define DEFAULT_MIME "text/plain"

ESP8266WebServer server(80);
String response = "";
bool SYSTEM_CONTROL_OVERRIDE = 0;
bool r1 = 0, r2 = 0;
int overrideTimeout = 0;

void getId(){
    server.send(HTTP_OK_CODE, DEFAULT_MIME, AP_SSID);
}

void rotationRelayControlOverride(){
  if(SYSTEM_CONTROL_OVERRIDE){
    overrideTimeout = millis();
    if(GLOBAL_RELAY_STATES[ROT_RELAY]){
      setRelayState(ROT_RELAY, LOW);
      server.send(HTTP_OK_CODE, DEFAULT_MIME, "Rotation:LOW");
    }else{
      setRelayState(ROT_RELAY, HIGH);
      server.send(HTTP_OK_CODE, DEFAULT_MIME, "Rotation:HIGH");
    }
  }else{
        server.send(HTTP_OK_CODE, DEFAULT_MIME, "Enable Manual Override");
  }
}

void enableControlOverride(){
  if(SYSTEM_CONTROL_OVERRIDE){
    SYSTEM_CONTROL_OVERRIDE = 0;
  }else{
    SYSTEM_CONTROL_OVERRIDE = 1;
    overrideTimeout = millis();
  }
  server.send(HTTP_OK_CODE, DEFAULT_MIME, String(SYSTEM_CONTROL_OVERRIDE));
}

void getStatusData(){
  
  response += String(0)+",";
  response += String(0)+",";
  response += String(0)+",";
  response += String(0)+",";
  response += String(0)+",";
  
  response += String(GLOBAL_ROT_CONTROL)+",";
  response += String(SYSTEM_CONTROL_OVERRIDE)+",";
  response += String(1)+",";
  response += String(GLOBAL_RELAY_STATES[ROT_CONTROL_RELAY_1])+",";
  response += String(GLOBAL_ROT_SLEEP_TIMER);
  
  server.send(HTTP_OK_CODE, DEFAULT_MIME, response);
  response = "";
}

void setParameters(){
  float temp1 = server.arg(0).toFloat();
  float temp2 = server.arg(1).toFloat();
  int rotation = server.arg(2).toInt();
  float tempOffset= server.arg(3).toFloat();
  int rotationSleep = server.arg(4).toFloat();
  saveParameters(temp1, temp2, rotation, tempOffset, rotationSleep);
  server.send(HTTP_OK_CODE, DEFAULT_MIME, "Parameters Set");
}

void resetICS(){
  server.send(HTTP_OK_CODE, DEFAULT_MIME, "Resetting");
  delay(3000);
  ESP.reset();  
}

void deadend(){
  server.send(HTTP_ERROR_CODE, DEFAULT_MIME, "");
}

void initServer(){
  server.on("/rotation", rotationRelayControlOverride);
  server.on("/override", enableControlOverride);
  server.on("/status", getStatusData);
  server.on("/params", setParameters);
  server.on("/reset", resetICS);
  server.on("/id", getId);
  server.onNotFound(deadend);
  server.begin();
}

void handleRequest(){
  if(millis() - overrideTimeout >= OVERRIDE_TIMEOUT){
    SYSTEM_CONTROL_OVERRIDE = 0;
  }
  server.handleClient();
}
