#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>
TinyGPSPlus gps;

#define TX D3
#define RX D2

SoftwareSerial gpsDeviceSerial(TX, RX);

double GLOBAL_GPS_LAT, GLOBAL_GPS_LON, GLOBAL_GPS_SPEED;
char c;
    
void initGPS(int bitrate)
{
  gpsDeviceSerial.begin(bitrate);
}

void getLocationData()
{
  bool newData = false;
  
  for (unsigned long start = millis(); millis() - start < 1000;){
    while (gpsDeviceSerial.available())
    {
      c = gpsDeviceSerial.read();
      Serial.print(c);
      if (gps.encode(c)){
        newData = true;
    }
  }

    if (newData){
      GLOBAL_GPS_LAT = gps.location.lat();
      GLOBAL_GPS_LON = gps.location.lng();
      GLOBAL_GPS_SPEED = gps.speed.kmph();
    } 
  }
}
