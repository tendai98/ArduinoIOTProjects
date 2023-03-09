#define HTTP_404_CODE         404
#define HTTP_501_CODE         501
#define HTTP_200_SCSS         200
#define HTTP_SVR_PORT         80

#define CONTENT_TYPE_TEXT     "text/text"
#define HTTP_404_MESSAGE      "404 Not Found"
#define HTTP_501_MESSAGE      "501 Not Implemented"
#define DEVICE_ID "TRACKER:0"

#include <ESP8266WebServer.h>
#include "buttons.h"

ESP8266WebServer webServer(HTTP_SVR_PORT);
String d = "";
char msg[32];
int newMessage = 0;

void pushMessage(){
  d = webServer.arg(0);  
  d.toCharArray(msg, 32);
  setString(msg, 8, 24);
  webServer.send(HTTP_200_SCSS, CONTENT_TYPE_TEXT, "Message Delivered"); 
  newMessage = 1;
}

void getSensorValues() {
  webServer.send(HTTP_200_SCSS, CONTENT_TYPE_TEXT, String(getBPM())+String(":")+String(getO2())); 
}

void getKeyScan(){
  int code = readKeyCode();
  webServer.send(HTTP_200_SCSS, CONTENT_TYPE_TEXT, String(code)); 
}

void getId(){
  webServer.send(HTTP_200_SCSS, CONTENT_TYPE_TEXT, DEVICE_ID);  
}

void notImplementedRoute(){
  webServer.send(HTTP_501_CODE, CONTENT_TYPE_TEXT, HTTP_501_MESSAGE);
}

void notFound(){
  webServer.send(HTTP_404_CODE, CONTENT_TYPE_TEXT, HTTP_404_MESSAGE);  
}

void handleClients(){
  webServer.handleClient();
}

void initHttp(){

  initButtons();
  webServer.onNotFound(notFound);
  webServer.on("/id", getId);
  webServer.on("/push", pushMessage);
  webServer.on("/sensors", getSensorValues);
  webServer.on("/keyscan", getKeyScan);
    
  webServer.begin();
}
