#include <LiquidCrystal_I2C.h>
#define LCD_I2C_ADDRESS 0x27

LiquidCrystal_I2C LCD(LCD_I2C_ADDRESS, 16, 2);

void initLCD(){
  LCD.init();
  LCD.backlight();
  LCD.clear();
}

void lcdPrintAt(char * dataBuffer, int col, int row){
  LCD.clear();
  LCD.setCursor(col, row);
  LCD.print(dataBuffer);
}

void setLCDCursor(int col, int row){
  LCD.setCursor(col, row);  
}

void lcdPrint(char * dataBuffer){
  LCD.print(dataBuffer);  
}

void lcdClear(){
  LCD.clear();
}
