#include "oled.h"
#include <RDA5807M.h>
#include <radio.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define TARGET_RADIO_BAND RADIO_BAND_FM
#define HTTP_SERVER_PORT 80
#define GROUP_RADIO_APNAME "GROUP-7-PROJECT"
#define GROUP_RADIO_PASSWD "qwertyuiop"
#define STATION_COUNT 4
#define VOLUME 4

int radioChannels[] = {10640, 9930, 8970, 9600};
int channelIndex = 0;

ESP8266WebServer server(HTTP_SERVER_PORT);
RDA5807M radio;

void initWiFi(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP(GROUP_RADIO_APNAME, GROUP_RADIO_PASSWD);
}

void initRadio(){
  radio.init();
  radio.setVolume(VOLUME);
  radio.setMono(false);
  radio.setMute(false);
}

void onNextChannel(){
  
  if(channelIndex == STATION_COUNT-1){
    channelIndex = 0;
  }else{  
    channelIndex++;
  }
  
  selectChannelIndex(channelIndex);
}

void onPrevChannel(){
  
  if(channelIndex == 0){
    channelIndex = 0;
  }else{   
    channelIndex--;
  }
  
  selectChannelIndex(channelIndex);
}


void initServer(){
  server.on("/next", onNextChannel);
  server.on("/prev", onPrevChannel);
  server.begin();
}

void selectChannelIndex(int channelIndex){
  
  radio.setBandFrequency(TARGET_RADIO_BAND, radioChannels[channelIndex]); 
  server.send(200, "text/plain", "CHANNEL!");
  
  switch(channelIndex){
    case 0:
         displayBottomRow("FM:   [106.40] MHZ"); 
         break;

    case 1:
         displayBottomRow("FM:   [099.30] MHZ"); 
         break;  

    case 2:
         displayBottomRow("FM:   [089.70] MHZ"); 
         break;       

    case 3:
         displayBottomRow("FM:   [096.00]MHZ"); 
         break;      
  }
  
  displayTopRow(" ***IOT RADIO***");
}

void setup(){
  initWiFi();
  initOLED();
  initRadio();
  initServer();
  selectChannelIndex(0);
}


void loop(){
  server.handleClient();
  delay(100);
}
