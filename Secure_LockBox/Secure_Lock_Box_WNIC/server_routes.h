bool authenticated = false;
bool otpState = false;

void unlockBox(){
    Serial.write(UNLOCK_OPCODE);
    server.send(HTTP_OK_CODE, DEFAULT_MIME, "Unlocked");
}

void lockBox(){
    Serial.write(LOCK_OPCODE);
    server.send(HTTP_OK_CODE, DEFAULT_MIME, "Locking Box...");  
}

void biometricAuth(){
    Serial.write(BIOAUTH_OPCODE);
    server.send(HTTP_OK_CODE, DEFAULT_MIME, "Using Biometric Authentication...");  
}

void enrollBiometric(){
    Serial.write(ENROLL_BIO_OPCODE);
    server.send(HTTP_OK_CODE, DEFAULT_MIME, "Switching to Enroll Mode");
}


void enableOTP(bool state){
   otpState = state;
}

void pinCodeAuth(){
  if(otpState){
      int inputOTP = server.arg(0).toInt();
      int savedOTP = 0;
      EEPROM.get(OTP_EEPROM_ADDRESS, savedOTP);
      
      if(savedOTP == inputOTP){
        Serial.write(UNLOCK_OPCODE);
        server.send(HTTP_OK_CODE, DEFAULT_MIME, "Authenticated");
        otpState = false;
      }else{
        server.send(HTTP_OK_CODE, DEFAULT_MIME, "Authentication Error");
      }
  }else{
        server.send(HTTP_OK_CODE, DEFAULT_MIME, "Scan Fingerprint First");    
  }
  
}

void setOTPAuthCode(){
  int otp = server.arg(0).toInt();
  EEPROM.put(OTP_EEPROM_ADDRESS, otp);
  EEPROM.commit();
  otp = -1;
  EEPROM.get(OTP_EEPROM_ADDRESS, otp);
  
  server.send(HTTP_OK_CODE, DEFAULT_MIME, "OTP Code Set"); 
}

void resetDevice(){
  Serial.write(RESET_OPCODE);
  ESP.reset();
}

void sendBoxId(){
  server.send(HTTP_OK_CODE, DEFAULT_MIME, DEV_SSID);  
}

void getGPSData(){
  server.send(HTTP_OK_CODE, DEFAULT_MIME, String(lat)+String(",")+String(lon));    
}


void nothing(){
  server.send(HTTP_404_CODE, DEFAULT_MIME, "Not Supported");
}
