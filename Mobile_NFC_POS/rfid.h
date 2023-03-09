#define SS_PIN  D4
#define RST_PIN D3

#include <SPI.h>
#include <MFRC522.h>

MFRC522 mfrc522(SS_PIN, RST_PIN);
String RFID_DATA = "";

void initRFID(){
  SPI.begin();
  mfrc522.PCD_Init();
}


int getUID() 
{
    delay(10);
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
    {
      RFID_DATA = "";
      return -1;
    }
    
    if ( ! mfrc522.PICC_ReadCardSerial()) 
    {
      RFID_DATA = "";
      return -1;
    }
    
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    {
       RFID_DATA.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
       RFID_DATA.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    
    RFID_DATA.toUpperCase();
    
    if (RFID_DATA.length() == 8) 
    {
      return 1;
    }

    return 3;
} 
