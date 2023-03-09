#include <WiFiUdp.h>
#include <ESP8266WebServer.h>


#define DEFAULT_PORT 2020
#define MAX_LEN 2

WiFiUDP server;
ESP8266WebServer dataServer(80);

char commandData[MAX_LEN];
int * command;

void getCurrentData(){
  dataServer.send(200, "text/plain", String(currentReading()));
}

void startServer(){
    dataServer.on("/amp", getCurrentData);
    dataServer.begin();
    server.begin(DEFAULT_PORT);
}


void scanServerData(){
  dataServer.handleClient();
  byte len = server.parsePacket();
  
  if(len){
        server.read(commandData,MAX_LEN);
        command = (int*) &commandData;
        systemControl(*command); 
  }
}
