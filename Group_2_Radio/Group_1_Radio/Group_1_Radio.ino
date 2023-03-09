#include <RDA5807M.h>
#include <radio.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define TARGET_RADIO_BAND RADIO_BAND_FM
#define HTTP_SERVER_PORT 80
#define LCD_I2C_ADDRESS 0x27
#define GROUP_RADIO_APNAME "G6-FMRADIO"
#define GROUP_RADIO_PASSWD "12345678"
#define STATION_COUNT 4
#define VOLUME 4

int radioChannels[] = {10640, 9930, 8970, 9600};
int channelIndex = 0;

ESP8266WebServer server(HTTP_SERVER_PORT);
LiquidCrystal_I2C lcd(LCD_I2C_ADDRESS,16,2);
RDA5807M radio;

void initWiFi(){
  WiFi.mode(WIFI_AP);
  WiFi.softAP(GROUP_RADIO_APNAME, GROUP_RADIO_PASSWD);
}

void initLCD(){
  lcd.init();
  lcd.clear();         
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(" *** [G--6] *** "); 
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
  server.on("/change_next", onNextChannel);
  server.on("/change_prev", onPrevChannel);
  server.begin();
}

void selectChannelIndex(int channelIndex){
  
  radio.setBandFrequency(TARGET_RADIO_BAND, radioChannels[channelIndex]); 
  server.send(200, "text/plain", "CHANNEL!");
  lcd.setCursor(0,1);
  
  switch(channelIndex){
    case 0:
          lcd.print("Zee FM:106.4Mhz"); 
          break;

    case 1:
          lcd.print("Power FM:99.6Mhz"); 
          break;  

    case 2:
          lcd.print("Star FM:89.7 Mhz"); 
          break;       

    case 3:
          lcd.print("RadioZim:96.0Mhz"); 
          break;      
  }
}

void setup(){
  initWiFi();
  initLCD();
  initRadio();
  initServer();
  selectChannelIndex(0);
}


void loop(){
  server.handleClient();
  delay(100);
}
