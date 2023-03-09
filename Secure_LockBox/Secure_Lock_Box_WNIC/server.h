#include <ESP8266WebServer.h>
#include <EEPROM.h>

#define OTP_EEPROM_ADDRESS 0x00000000
#define PORT 80

ESP8266WebServer server(PORT);

#include "server_routes.h"

void initServer(){
  EEPROM.begin(20);

  server.on("/id", sendBoxId);  
  server.on("/unlock", unlockBox);
  server.on("/lock", lockBox);
  server.on("/bioauth", biometricAuth);
  server.on("/bioenroll", enrollBiometric);
  server.on("/otpauth",  pinCodeAuth);
  server.on("/otpdump", setOTPAuthCode);
  server.on("/reset", resetDevice);
  server.on("/gps", getGPSData);
  server.onNotFound(nothing);

  server.begin();
}

void runServer(){
  server.handleClient();
}
