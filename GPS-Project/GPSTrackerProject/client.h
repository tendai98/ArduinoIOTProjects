#define HTTPS_PORT 443

WiFiClientSecure client;
String GLOBAL_DATA;

void httpGet(char * host){
  client.setInsecure();
  
    if(client.connect(host, HTTPS_PORT)){
      client.print(
        String("GET ") + GLOBAL_DATA + " HTTP/1.1\r\n" +
        "Host: " + host + "\r\n" + 
        "Connection: close\r\n\r\n"
      );  
  }
}
