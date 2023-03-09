#include "FirebaseESP8266.h"

#define FIREBASE_URL        "https://parking-sensors-system-default-rtdb.firebaseio.com/"
#define DATABASE_SECRET     "JRYKHLCzeExaQz2oSRjHH0pyFZ4PF6IGOmrXokrs"

FirebaseData firebaseData;
int extractIntData(FirebaseData &firebaseDataPtr);

void Firebase_up(){
  
  Firebase.begin(FIREBASE_URL, DATABASE_SECRET);
  Firebase.reconnectWiFi(true);
  
  firebaseData.setBSSLBufferSize(1024, 1024);
  firebaseData.setResponseSize(1024);

  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
  
}

bool set(String &path, int value){

  if(Firebase.setInt(firebaseData ,path,value )){
    return true;
  }else{
    return false;
  }
 
}

int get(String &path){
   Firebase.getInt(firebaseData, path);
   return extractIntData(firebaseData);
}

int extractIntData(FirebaseData &firebaseDataPtr){
  return firebaseDataPtr.intData();
}
