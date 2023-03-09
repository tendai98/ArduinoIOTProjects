#define HTTPS_PORT 443

WiFiClientSecure client;

void httpGet(char * host, char * url){
  client.setInsecure();
  
    if(client.connect(host, HTTPS_PORT)){
      client.print(
        String("GET ") + url + " HTTP/1.1\r\n" +
        "Host: " + host + "\r\n" + 
        "Connection: close\r\n\r\n"
      );  
  }
}
