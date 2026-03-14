//NIVEDITHA.E
#include <TinyGPS++.h>
#include<SoftwareSerial.h>
#include <TinyGPSPlus.h>



SoftwareSerial gpsSerial(8,9);
TinyGPSPlus gps;
float lattitude,longitude;

void setup() {

 gpsSerial.begin(4800);
 Serial.begin(9600);
  
  }

void loop()
{
  while (gpsSerial.available())
  {
    int data = gpsSerial.read();
    if (gps.encode(data))
    {
      lattitude = (gps.location.lat());
      longitude = (gps.location.lng());
      Serial.print ("lattitude: ");
      Serial.println (lattitude);
      Serial.print ("longitude: ");
      Serial.println (longitude);
    }
  }
}

