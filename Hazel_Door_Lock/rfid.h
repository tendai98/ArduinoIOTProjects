
#define SS_PIN  D8
#define RST_PIN D0
#define ACCESS_UID "45 2E 6A 30"

#include <SPI.h>
#include <MFRC522.h>

MFRC522 mfrc522(SS_PIN, RST_PIN);
String data = "";

void initRFID(){
  SPI.begin();
  mfrc522.PCD_Init();
}


int getUID() 
{
    delay(10);
    if ( ! mfrc522.PICC_IsNewCardPresent()) 
    {
      data = "";
      return -1;
    }
    
    if ( ! mfrc522.PICC_ReadCardSerial()) 
    {
      data = "";
      return -1;
    }
    
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    {
       data.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
       data.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    
    data.toUpperCase();
    
    if (data.substring(1) == ACCESS_UID) 
    {
      data = "";
      return 1;
    }
    
    else   {
      data = "";
      return 3;
    }
} 
