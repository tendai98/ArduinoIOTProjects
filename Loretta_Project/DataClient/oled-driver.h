#include <U8g2lib.h>
#include <Wire.h>
#define Y_POS 25
#define X_POS 8

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); // Setup U8G2 Controller Object

void initOLED(){
  u8g2.begin();
  u8g2.setFont(u8g2_font_tenthinguys_tf); 
}

void clearScreenBuffer(){
   u8g2.clearBuffer();
}

void printChar(char c){
   char b[1] = {c};
   u8g2.drawStr(X_POS, Y_POS, b);
   u8g2.sendBuffer();  
}

void setChar(char c, int x, int y){
   char b[1] = {c};
   u8g2.drawStr(x, y, b);
   u8g2.sendBuffer();  
}

void printString(char * ptr){
  
   u8g2.clearBuffer();
   u8g2.drawStr(X_POS, Y_POS, ptr);
   u8g2.sendBuffer();  
}

void setString(char * ptr, int x, int y){

   u8g2.clearBuffer();
   u8g2.drawStr(x, y, ptr);
   u8g2.sendBuffer();
}
