#include <ESP32Lib.h>
#include <Ressources/Font6x8.h>

#define RED_GPIO    14
#define GREEN_GPIO  19
#define BLUE_GPIO   27
#define HSYNC_GPIO  32
#define VSYNC_GPIO  33

#define INTRO_BANNER "-------[TELONE CENTER FOR LEARNING NOTICE BOARD]-----"

VGA3Bit vga;

void initVGA()
{
  vga.init(vga.MODE320x240, RED_GPIO, GREEN_GPIO, BLUE_GPIO, HSYNC_GPIO, VSYNC_GPIO);
  vga.setFont(Font6x8);
}

void vgaPrintBuff(char * buff)
{
  vga.println(buff);
}

void vgaPrintLine(){
  vga.println("");
}

void vgaClear(){
  vga.setCursor(0,0);
  vga.clear(vga.RGBA(0,0,0));
  vgaPrintBuff(INTRO_BANNER);
}
