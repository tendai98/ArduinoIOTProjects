#include <TinyGPS++.h>
TinyGPSPlus gpsParser;

void startSerial(int bitrate){
  Serial.begin(bitrate);
}

void updateGPS(){
  char c = 0;
   while(Serial.available()){
      gpsParser.encode(c);
   }
}

double getLongitude(){
  updateGPS();
  return gpsParser.location.lng();
}

double getLatitude(){
  updateGPS();
  return gpsParser.location.lat();
}
