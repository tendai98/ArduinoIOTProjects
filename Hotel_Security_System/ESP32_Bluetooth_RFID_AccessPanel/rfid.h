#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5
#define RST_PIN 27
#define NO_CARD_PRESENT 0x0fffff00
#define CARD_READ_ERROR 0x0fffff01

MFRC522 RFID(SS_PIN, RST_PIN);
int * rfidCardUID;
  
void initRFID(){
  SPI.begin();
  RFID.PCD_Init();
}


int readRFID(){
  
  if (RFID.PICC_IsNewCardPresent()) {
    if (RFID.PICC_ReadCardSerial()) {
      rfidCardUID = (int*) RFID.uid.uidByte;
      RFID.PICC_HaltA();
      RFID.PCD_StopCrypto1();
      return *rfidCardUID;
    }else{
      return CARD_READ_ERROR;
    }
  }else{
      return NO_CARD_PRESENT;
  }
}
