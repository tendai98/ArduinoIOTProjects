#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#include "const.h"
#include "fps.h"
#include "gps.h"
#include "servo.h"

char opcode;

void setup() {
  
  lcd.init();
  lcd.clear();
  lcd.backlight();
  initServo();
  Serial.begin(9600);
}

void executeOpcode(char opcode){
  
   switch(opcode){
     case ENROLL_BIO_OPCODE:
        enrollFingerprints();
        delay(1000);
        lcd.clear();
        break;

     case BIOAUTH_OPCODE:
        if(scanFingerprint() != -1){
          lcd.clear();
          lcd.print("Enter OTP");
          Serial.write(BIOAUTH_OK_OPCODE);
        }else{
          lcd.clear();
          lcd.print("Invalid Prints");
        }
        delay(1000);
        break;

     case LOCK_OPCODE:
        lcd.clear();
        lcd.print("[!] Locked");
        runLockProc();
        break;

     case UNLOCK_OPCODE:
         lcd.clear();
         lcd.print("[+] Unlocked");
         runUnLockProc();
         break;       
   }   
}

void loop() {
  
  while(Serial.available()){
    lcd.clear();
    shutdownGPS();
    opcode = Serial.read();
    executeOpcode(opcode);
    delay(3000);
  }

  lcd.setCursor(0,0);
  lcd.print("[Kudzi  Sithole]");
  lcd.setCursor(0,1);
  lcd.print("Secure Lock Box");
  sendGPSData();
  delay(1000);
}
