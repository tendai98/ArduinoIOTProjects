#include <Adafruit_Fingerprint.h>
#include "SoftwareSerial.h"

#define SYS_SCAN_MODE 'A'
#define SYS_PROG_MODE 'B'
#define SYS_FLSH_FPS 'X'
#define SYS_GET_RFID 'W'
#define SYS_RFID_SCAN 'T'

#define SYS_CAPTURE_CODE 'C'
#define SYS_PLACE_FINGER 'D'
#define SYS_GOT_BIOMETRIC 'E'
#define SYS_OPERATION_FAIL 'F'
#define SYS_REMOVE_FINGER 'G'
#define SYS_PLACE_AGAIN 'H'
#define SYS_SCAN_COMPLETE 'I'
#define GPS_GOT_PRINT 'J'
#define SYS_PRINT_MATCH 'K'
#define SYS_NO_MATCH 'L'
#define SYS_ENROLLED 'M'
#define SYS_DEVICE_READY 'N'
#define SYS_DEVICE_NULL  'O'
#define SYS_FAILED_STORE 'P'
#define SYS_SCANNING_PRG 'Q'
#define SYS_ACCESS_GRANT 'R'
#define SYS_ACCESS_DENID 'S'
#define SYS_OPERXN_DONE  'Z'
#define SYS_OPERXN_FAIL  'Y'

SoftwareSerial fps(2,3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&fps);

int getRandomID(){
  return random(1,127);
}

int runProc(){
  int code = -1;
  
  while(code != FINGERPRINT_OK){
      code = finger.getImage();
      if(code == FINGERPRINT_OK){
        Serial.println(SYS_CAPTURE_CODE);
        break;
      }else{
        Serial.println(SYS_PLACE_FINGER);
      }
      delay(100);
  }

  code = finger.image2Tz(1);

  if(code == FINGERPRINT_OK){
      Serial.println(SYS_GOT_BIOMETRIC);
      delay(100);
  }else{
      Serial.println(SYS_OPERATION_FAIL);
      return -1;
  }

  Serial.println(SYS_REMOVE_FINGER);
  delay(1000);
  
  Serial.println(SYS_PLACE_AGAIN);
  code = 0;
  while (code != FINGERPRINT_NOFINGER){
      code = finger.getImage();
  }

  code = -1;
  while(1){
     if(code != FINGERPRINT_OK){
       code  = finger.getImage(); 
     }else{
        Serial.println(SYS_SCAN_COMPLETE);
        break;
     }
  }

  code = finger.image2Tz(2);

  if(code == FINGERPRINT_OK){
    Serial.println(GPS_GOT_PRINT);
  }else{
    Serial.println(SYS_OPERATION_FAIL);
    return -1;
  }

  delay(1000);
  code = finger.createModel();
  
  if(code == FINGERPRINT_OK){
    Serial.println(SYS_PRINT_MATCH);
  }else{
    Serial.println(SYS_NO_MATCH);
    return -1;
  }

  delay(1000);
  int id = getRandomID();
  code = finger.storeModel(id);
  if(code == FINGERPRINT_OK){
    Serial.println(SYS_ENROLLED);
    delay(1000);
    Serial.println(id);
    return 0;
  }else{
    Serial.println(SYS_FAILED_STORE);
    return -1;
  }
}

void enrollFingerprints(){
  randomSeed(analogRead(A0));
  finger.begin(57600);
  delay(1000);
  if(finger.verifyPassword()){
    
    int code = -1;
    while(code == -1){
      code = runProc();
    }
    
  }else{
    Serial.println(SYS_DEVICE_NULL);
  }
  fps.end();
}

int scanFingerprint(){
  randomSeed(analogRead(A0));
  finger.begin(57600);
  delay(1000);
  
  int code = -1;
  
  while(code != FINGERPRINT_OK){

    code = finger.getImage(); 
    Serial.println(SYS_SCANNING_PRG);
    delay(250);
     code = finger.image2Tz();
     
     if(code == FINGERPRINT_OK){
       code = finger.fingerSearch();
       
       if(code == FINGERPRINT_OK){
          Serial.println(SYS_ACCESS_GRANT);
          delay(1000);
          fps.end();
          return finger.fingerID;
       }else{
          Serial.println(SYS_ACCESS_DENID);
          delay(1000);
       }
     }else{
       delay(100);
     }
  }

  fps.end();
  return -1;
}

void flushFPS(){
  finger.begin(57600);
  delay(1000);
  int p;
  
  for (int id = 1; 128 > id; id++){
      p = finger.deleteModel(id);
      if (p == FINGERPRINT_OK) {
          Serial.println(SYS_OPERXN_DONE);
      }else{
          Serial.println(SYS_OPERXN_FAIL);
      }
  }
  fps.end();
}
