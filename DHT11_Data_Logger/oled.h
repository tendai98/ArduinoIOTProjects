#include <U8g2lib.h>
#define SDA_PIN 3
#define SCL_PIN 1


U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, SCL_PIN, SDA_PIN, U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED
#define ERROR_MSG "DATA ERROR"

void initOLED(void) {
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_tenthinguys_tf);
  
}

void displayData(void) {
  u8g2.clearBuffer(); 
  if(GLOBAL_HMD <= 100 && GLOBAL_TEMP <= 100 && !isnan(GLOBAL_TEMP) || !isnan(GLOBAL_HMD)){
    msg1 = "--> tC: "+String(GLOBAL_TEMP);
    msg2 = "--> h%: "+String(GLOBAL_HMD);
    u8g2.drawStr(24, 12, msg1.c_str());  
    u8g2.drawStr(24, 28, msg2.c_str()); 
  }else{
    u8g2.drawStr(30, 16, ERROR_MSG);  
  }
  u8g2.sendBuffer();
}
