#include "dht.h"
#include "oled.h"
#include "sdcard.h"

#define DATA_LOG_FILE "/datalog.txt"

void setup() {
  Serial.begin(115200);
  initDHT();
  initSDM_MMC();
}

void loop() {
  getSensorData();
  if(appendFile(SD_MMC, DATA_LOG_FILE, logData.c_str())){
    Serial.println("[+] DATA DUMP SUCCESS");
  }else{
    Serial.println("[!] DATA DUMP FAILED");
  }
  delay(1000);
}
