#include "gps.h"

#define HOST "utrack-console.herokuapp.com"
#define TRACKER_NODE_ID "Goat-1"
#define HTTPS_PORT 443

WiFiClientSecure client;

int lt , ln;

void httpGet(){
    client.setInsecure();
      
    ln = GLOBAL_GPS_LON;
    lt = GLOBAL_GPS_LAT;

    if(ln && lt){
        if(client.connect(HOST, HTTPS_PORT)){
         
          client.printf(
            "GET /api?longitude=%f&latitude=%f&id=%s HTTP/1.1\r\n",
             GLOBAL_GPS_LON, GLOBAL_GPS_LAT, TRACKER_NODE_ID);
            
          client.printf("Host: %s\r\nConnection: close\r\n\r\n", HOST);
          blinkLED();
        }
    }
}
