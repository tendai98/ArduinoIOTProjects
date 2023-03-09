#include "bluetooth.h"
#include "lcd.h"
#include "rfid.h"
#include "servo.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <HTTPClient.h>

HTTPClient http;
WiFiClient client;

#define AP_SSID "HotelSensorGrid"
#define AP_PASS "1234567890"
#define DEFAULT_BAUDRATE 9600

int id = 0;
String sensorData;

void bootMessage(){
  lcdPrintAt("LOADING...", 0, 1);
  setLCDCursor(0,0);
  delay(2000);
  
  for(int count=0; count<16; count++){
    lcdPrint("-");
    delay(300); 
  }
  
  delay(2000);
  lcdClear();
}


void initWiFi(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(AP_SSID, AP_PASS);
  while(WiFi.status() != WL_CONNECTED){
    delay(100);
  }
}

void getSensorData(){
  
  http.begin(client, "http://192.168.4.1/sensors");  // begin HTTP GET using given URL
  int errorCode = http.GET(); // Send HTTP GET
  if(errorCode > 0){
     sensorData = http.getString(); // Read return string
  }
  http.end();

}

void recvSerialData(){
  if(Serial.available()){
    int cmd = (int) ((char) Serial.read());
    switch(cmd){

        case 0x58:
          driveServo(0);
          break;
          
        case 0x55:
          driveServo(0);
          delay(2000);
          driveServo(90);
          break;
          
        case 0x4c:
          driveServo(90);
          break;
    }
    Serial.flush();
  }
}

void rfidAccessMethod(){
  id = readRFID();
  if(id == NO_CARD_PRESENT){
      lcdPrintAt("  [Place Card]  ",0, 1);
      delay(1000);  
  }else if(id == CARD_READ_ERROR){
      lcdPrintAt("Card Read Error ",0, 1);  
      delay(1000);  
  }else{
      lcdPrintAt("RFID-CARD ACCESS",0, 1);   
      Serial.printf("SC-ACM:%08x\n", id);   
      delay(1000); 
  }
  recvSerialData();
}

void bluetoothAccessMethod(){
  char * pin_ptr = recvBTData();
  if(pin_ptr[0] != 0){
     lcdPrintAt(" AUTH-APP ACCESS",0, 1); 
     Serial.printf("BT-ACM:%s\n", pin_ptr);   
     resetBTBuffer();
     delay(1000);
  }else{
     lcdPrintAt(" [Use Auth-App] ",0, 1);
     delay(1000);  
  }
}

void setup(){
  Serial.begin(DEFAULT_BAUDRATE);
  initWiFi();
  initLCD();
  initRFID();
  initServo();
  initBluetooth();
  bootMessage();
  driveServo(0);
}

void loop(){
  rfidAccessMethod();
  bluetoothAccessMethod();
  
  getSensorData();
  Serial.printf("SSD:%s\n",sensorData.c_str());
}
