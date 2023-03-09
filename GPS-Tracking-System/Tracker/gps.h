#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>

#define DEFAULT_BITRATE 9600
#define TX D7
#define RX D8

TinyGPSPlus dataParser;
SoftwareSerial serialDevice(TX, RX);

double GLOBAL_GPS_LAT, GLOBAL_GPS_LON, GLOBAL_GPS_SPEED;
char c;
    
void initGPS()
{
  serialDevice.begin(DEFAULT_BITRATE);
}

void getLocationData()
{
  while (serialDevice.available())
  {
    c = serialDevice.read();
    if (dataParser.encode(c)){
      GLOBAL_GPS_LAT = dataParser.location.lat();
      GLOBAL_GPS_LON = dataParser.location.lng();
    }
  }
}
