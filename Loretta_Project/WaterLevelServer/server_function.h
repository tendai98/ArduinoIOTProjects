#define ANALOG_SENSOR_PIN     A0


void getSensorValue() {  
  int value = analogRead(A0);
  webServer.send(HTTP_200_SCSS, CONTENT_TYPE_TEXT, String(value)); 
}

void notFound(){
  webServer.send(HTTP_404_CODE, CONTENT_TYPE_TEXT, HTTP_404_MESSAGE);  
}
