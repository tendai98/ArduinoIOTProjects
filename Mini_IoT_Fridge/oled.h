#include <U8g2lib.h>
#define SDA_PIN D2
#define SCL_PIN D1

U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, SCL_PIN, SDA_PIN, U8X8_PIN_NONE);   // Adafruit Feather ESP8266/32u4 Boards + FeatherWing OLED

void initOLED(void) {
  u8g2.begin();
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_tenthinguys_tf);
  
}

void displayTopRow(const char * string_ptr) {
  u8g2.drawStr(0, 12, string_ptr);
  u8g2.sendBuffer();
}

void displayBottomRow(const char * string_ptr) {
  u8g2.drawStr(24, 32, string_ptr);
  u8g2.sendBuffer();
}

void displayString(const char * string_ptr, int x, int y) {
  u8g2.clearBuffer();
  u8g2.drawStr(x,y, string_ptr);
  u8g2.sendBuffer();
}

void clearScreen(){
  u8g2.clearBuffer();
}
