#include <WebServer.h>

WebServer server(81);

#define TCM_ID "TCM-00000001"

#define HTTP_OK_CODE 200

#define RED_GPIO 15
#define AMBER_GPIO 14
#define GREEN_GPIO 2
#define FLASH_GPIO 4

#define FLASH_ON_MSG "FLASH ACTIVATED"
#define FLASH_OFF_MSG "FLASH DEACTIVATED"
#define RED_ON_MSG "RED ACTIVATED"
#define RED_OFF_MSG "RED DEACTIVATED"
#define AMBER_ON_MSG "AMBER ACTIVATED"
#define AMBER_OFF_MSG "AMBER DEACTIVATED"
#define GREEN_ON_MSG "GREEN ACTIVATED"
#define GREEN_OFF_MSG "GREEN DEACTIVATED"

void flash_on_handler(){
  digitalWrite(FLASH_GPIO, HIGH);
  server.send(HTTP_OK_CODE, "text/plain", FLASH_ON_MSG);  
}

void flash_off_handler(){
  digitalWrite(FLASH_GPIO, LOW);
  server.send(HTTP_OK_CODE, "text/plain", FLASH_OFF_MSG);  
}


void red_on_handler(){
  digitalWrite(RED_GPIO, HIGH);
  server.send(HTTP_OK_CODE, "text/plain", RED_ON_MSG);  
}

void red_off_handler(){
  digitalWrite(RED_GPIO, LOW);
  server.send(HTTP_OK_CODE, "text/plain", RED_OFF_MSG);  
}

void amber_on_handler(){
  digitalWrite(AMBER_GPIO, HIGH);
  server.send(HTTP_OK_CODE, "text/plain", AMBER_ON_MSG);  
}

void amber_off_handler(){
  digitalWrite(AMBER_GPIO, LOW);
  server.send(HTTP_OK_CODE, "text/plain", AMBER_OFF_MSG);  
}

void green_on_handler(){
  digitalWrite(GREEN_GPIO, HIGH);
  server.send(HTTP_OK_CODE, "text/plain", GREEN_ON_MSG);  
}

void green_off_handler(){
  digitalWrite(GREEN_GPIO, LOW);
  server.send(HTTP_OK_CODE, "text/plain", GREEN_OFF_MSG);  
}

void get_dev_id(){
  server.send(HTTP_OK_CODE, "text/plain", TCM_ID);
}

void reset_dev(){
  ESP.restart();
}


void initServer(){

    pinMode(RED_GPIO, OUTPUT);
    pinMode(AMBER_GPIO, OUTPUT);
    pinMode(GREEN_GPIO, OUTPUT);  

    digitalWrite(RED_GPIO, LOW);
    digitalWrite(AMBER_GPIO, LOW);
    digitalWrite(GREEN_GPIO, LOW);


    server.on("/flash:1", flash_on_handler);
    server.on("/flash:0", flash_off_handler);
    server.on("/red:1", red_on_handler);
    server.on("/red:0", red_off_handler);
    server.on("/amber:1", amber_on_handler);
    server.on("/amber:0", amber_off_handler);
    server.on("/green:1", green_on_handler);
    server.on("/green:0", green_off_handler);
    server.on("/reset", reset_dev);
    server.on("/id", get_dev_id);

    server.begin();
}

void handleRequests(){
  server.handleClient();
}
