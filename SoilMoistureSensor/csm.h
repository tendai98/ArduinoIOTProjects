const int SensorPin = A0;
int AirValue = 790;   
int WaterValue = 390;
int soilMoistureValue = 0;
int soilMoisturePercent = 0;

int getSoilMoistureValue() 
{
  soilMoistureValue = analogRead(SensorPin);  //put Sensor insert into soil
  soilMoisturePercent = map(soilMoistureValue, AirValue, WaterValue, 0, 100);
  
  if(soilMoisturePercent > 100)
  {
      return 100;
  }
  else if(soilMoisturePercent < 0)
  {
      return 0;
  }
  else if(soilMoisturePercent >=0 && soilMoisturePercent <= 100)
  {
    return soilMoisturePercent;
  }  
}
