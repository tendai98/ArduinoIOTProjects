#define HOST "air-sense-117.herokuapp.com"
#define SENSOR_NODE_ID "GS-0000000000000000"
#define HTTPS_PORT 443
#define SENSOR_IO A0

WiFiClientSecure client;
int dataValue = 0;

void httpGet(){
    client.setInsecure();
    dataValue = analogRead(SENSOR_IO);
    
    if(client.connect(HOST, HTTPS_PORT)){     
      client.printf(
        "GET /api?value=%d HTTP/1.1\r\n", dataValue);
      client.printf("Host: %s\r\nConnection: close\r\n\r\n", HOST);
    }
}
