#include <TinyGPS.h>
TinyGPS gps;

#define ss Serial

float flat, flon;
unsigned long age;
    
void initGPS(int bitrate)
{
  ss.begin(bitrate);
}

void getLocationData()
{
  bool newData = false;
  
  for (unsigned long start = millis(); millis() - start < 1000;){
    while (ss.available())
    {
      char c = ss.read();
      if (gps.encode(c)){
        newData = true;
    }
  }

    if (newData){
      gps.f_get_position(&flat, &flon, &age);
    } 
  }
}
