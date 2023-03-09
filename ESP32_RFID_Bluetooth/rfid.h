#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN                0x00000005 
#define RST_PIN               0x0000001b
#define BLOCK_ADDRESS         0x00000004
#define TRAILER_BLOCK         0x00000007

//DEVICE RFID ERROR RETURN CODES
#define RFID_AUTH_FAILED_CODE 0x00000031
#define RFID_WRIT_FAILED_CODE 0x00000032
#define RFID_READ_FAILED_CODE 0x00000033
#define RFID_CARD_DETECT_CODE 0x00000034
#define RFID_OPRX_SUCCES_CODE 0x00000035
#define RFID_CARD_SELECT_CODE 0x00000036

// DEVICE COMMAND OPCODES
#define RFID_READ_OPCODE_CODE 0x00000037
#define RFID_WRIT_OPCODE_CODE 0x00000038
#define RFID_PUSH_DATA_OPCODE 0x00000039
#define RFID_PULL_DATA_OPCODE 0x00000030

// APPENDED CODES & OPCODES
#define RFID_OPRX_FAILED_CODE 0x00000041
#define RFID_RESET_MCU_OPCODE 0x00000042

MFRC522 rfid(SS_PIN, RST_PIN);
MFRC522::MIFARE_Key key;
MFRC522::StatusCode status;

byte GLOBAL_DATA_BLOCK[16];
byte GLOBAL_DATA_BUFFER[18];
byte dataLen;

void initKey(){
  for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
  }
}

void initRFID() {
  SPI.begin();
  rfid.PCD_Init();
  initKey();
  dataLen = sizeof(GLOBAL_DATA_BUFFER);
}

int writeRFIDData(){
  if (!rfid.PICC_IsNewCardPresent())
        return RFID_CARD_DETECT_CODE;

  if (!rfid.PICC_ReadCardSerial())
      return RFID_CARD_SELECT_CODE;
  
  status = (MFRC522::StatusCode) rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, TRAILER_BLOCK, &key, &(rfid.uid));
  if (status != MFRC522::STATUS_OK) {
      return RFID_AUTH_FAILED_CODE;
  }
  
  status = (MFRC522::StatusCode) rfid.MIFARE_Write(BLOCK_ADDRESS, GLOBAL_DATA_BLOCK, 16);
  if (status != MFRC522::STATUS_OK) {
        return RFID_WRIT_FAILED_CODE;
  }else{
    rfid.PICC_HaltA();
    rfid.PCD_StopCrypto1();
    return RFID_OPRX_SUCCES_CODE;
  }
}

int readRFIDData(){
  if (!rfid.PICC_IsNewCardPresent())
        return RFID_CARD_DETECT_CODE;

  if (!rfid.PICC_ReadCardSerial())
      return RFID_CARD_SELECT_CODE;
      
  status = (MFRC522::StatusCode) rfid.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, TRAILER_BLOCK, &key, &(rfid.uid));
  if (status != MFRC522::STATUS_OK) {
      return RFID_AUTH_FAILED_CODE;
  }
  
 status = (MFRC522::StatusCode) rfid.MIFARE_Read(BLOCK_ADDRESS, GLOBAL_DATA_BUFFER, &dataLen);
    if (status != MFRC522::STATUS_OK) {
        return RFID_READ_FAILED_CODE;
    }else{
        rfid.PICC_HaltA();
        rfid.PCD_StopCrypto1();
        return RFID_OPRX_SUCCES_CODE; 
    }
}
