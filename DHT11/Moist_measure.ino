#include "DHT.h"

DHT dht;
float Humidity, Temperature;

void setup(void){
  Serial.begin(115200);         /*Set the baudrate to 115200*/
  dht.setup(0);                 /*Connect the DHT11's data pin to GPIO0*/
  Serial.println("Status\tHumidity (%)\tTemperature (C)\t(F)");
  delay(1000);                  /*Wait for 1000mS*/
}

void loop(void){
  Temperature = dht.getTemperature(); /*Get the Temperature value*/
  Humidity = dht.getHumidity();       /*Get the Humidity value*/
 
  Serial.print(dht.getStatusString());/*Get the Status of DHT11 Sensor*/
  Serial.print("\t");
  Serial.print(Humidity, 1);
  Serial.print("\t\t");
  Serial.println(Temperature, 1);

  delay(dht.getMinimumSamplingPeriod()*2);
}
