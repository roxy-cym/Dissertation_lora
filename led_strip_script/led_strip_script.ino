

#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>
#include <SoftwareSerial.h>


#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
//light strip
#define PIN 5
#define NUM 60
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM, PIN, NEO_GRB + NEO_KHZ800);
#define BRIGHTNESS 10
//Rssi number
//led number


//GPS
#include <TinyGPS++.h>
#include "wiring_private.h"
TinyGPSPlus gps;
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;
SoftwareSerial ss(RXPin, TXPin);

int lastcon = 0;
unsigned long last_update = 0;
uint8_t txBuffer[8];
String latitudeBinary, longitudeBinary;
uint16_t altitudeGps;
uint8_t hdopGps;

const int rows = 51;
const int columns = 3;
float myreadings[rows][columns] =
{
-81  , 51.54118  , -0.01441  ,
-89 , 51.54114  , -0.01447  ,
-92 , 51.54110  , -0.01449  ,
-93 , 51.54107  , -0.01452  ,
-83 , 51.54103  , -0.01458  ,
-86 , 51.54097  , -0.01460  ,
-81 , 51.54085  , -0.01464  ,
-79 , 51.54081  , -0.01464  ,
-84 , 51.54073  , -0.01467  ,
-91 , 51.54068  , -0.01467  ,
-83 , 51.54063  , -0.01464  ,
-91 , 51.54051  , -0.01454  ,
-89 , 51.54046  , -0.01439  ,
-86 , 51.54044  , -0.01434  ,
-81 , 51.54042  , -0.01430  ,
-91 , 51.54034  , -0.01415  ,
-87 , 51.54031  , -0.01409  ,
-80 , 51.54019  , -0.01394  ,
-75 , 51.54008  , -0.01385  ,
-71 , 51.54000  , -0.01372  ,
-89 , 51.53999  , -0.01366  ,
-91 , 51.54006  , -0.01346  ,
-85 , 51.54010  , -0.01334  ,
-79 , 51.54008  , -0.01327  ,
-79 , 51.54005  , -0.01321  ,
-81 , 51.54004  , -0.01314  ,
-83 , 51.54003  , -0.01308  ,
-74 , 51.54004  , -0.01293  ,
-85 , 51.54006  , -0.01282  ,
-81 , 51.54008  , -0.01276  ,
-92 , 51.54009  , -0.01276  ,
-77 , 51.54011  , -0.01274  ,
-82 , 51.54014  , -0.01271  ,
-75 , 51.54017  , -0.01269  ,
-81 , 51.54018  , -0.01265  ,
-92 , 51.54018  , -0.01261  ,
-90 , 51.54024  , -0.01252  ,
-86 , 51.54025  , -0.01243  ,
-77 , 51.54029  , -0.01237  ,
-77 , 51.54030  , -0.01233  ,
-87 , 51.54031  , -0.01233  ,
-93 , 51.54033  , -0.01231  ,
-79 , 51.54035  , -0.01228  ,
-86 , 51.54037  , -0.01224  ,
-85 , 51.54038  , -0.01224  ,
-89 , 51.54040  , -0.01222  ,
-92 , 51.54041  , -0.01220  ,
-92 , 51.54048  , -0.01209  ,
-83 , 51.54049  , -0.01207  ,
-92 , 51.54048  , -0.01205  ,
-89 , 51.54053  , -0.01198  ,
  };
  
/*
  -86, 51.5199,-0.1347,
-80,51.5212,-0.1349,
-90,51.5212,-0.1351,
-100,51.5211,-0.1350
*/
void setup() {
  // put your setup code here, to run once:
  // loop through array’s rows
  pixels.begin();
  pixels.setBrightness(BRIGHTNESS);
  Serial.begin(115200);
  ss.begin(GPSBaud);
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
  for ( int i = 0; i < rows; ++i ) {
    // loop through columns of current row
    for ( int j = 0; j < columns; ++j )
      Serial.print (myreadings[ i ][ j ] );
    Serial.println() ; // start new line of output
  }
}
void loop() {
  pixels.clear();
  while (ss.available() > 0){
        char c = ss.read();
        if (gps.encode(c)){ 
                //float  testlat = (gps.location.lat(), 6);
                //float  testlon = (gps.location.lng() + 180)/ 360.0;
                //Serial.println(testlat);
                //Serial.println(gps.location.lat(), 6);
                //Serial.println(gps.location.lng(), 6);
                float  testlat = (gps.location.lat());
                int new_lat=testlat*10000;
                float  testlon = (gps.location.lng());
                int new_lon=testlon*10000;
                //Serial.println(testlat,4);
                //Serial.println(testlon,4);
                Serial.println(new_lat);
                Serial.println(new_lon);
                
                //displayInfo();
  // put your main code here, to run repeatedly:
  // loop through array’s rows
  for ( int i = 0; i < rows; ++i ) {
    // loop through columns of current row
    //for ( int j = 0; j < columns; ++j ){
    //  Serial.print (myreadings[ i ][ j ] );
    //  Serial.print (” “);
    //}
    Serial.print(" Rssi: ");
    Serial.print(myreadings[ i ][ 0 ] );
    Serial.print(" Lat: ");
    Serial.print(myreadings[ i ][ 1 ], 4 ); 
    int new_reading_1 =myreadings[ i ][ 1 ]*10000;// comma 4 means show 4dp
    Serial.print(" Long: ");
    Serial.println(myreadings[ i ][ 2 ], 4 ); // comma 4 means show 4dp
    int new_reading_2 =myreadings[ i ][ 2 ]*10000;
    Serial.println(new_reading_1);
    Serial.println(new_reading_2);
    if ((new_reading_1 == new_lat) && (new_reading_2 == new_lon)) {
      Serial.print(" <<<< this is the one we want! ");
      Serial.print(" turn light to ");
      Serial.print(int(myreadings[ i ][ 0 ])+120);//120
      int ledNum=int(myreadings[ i ][ 0 ])+120;
      for (uint16_t i = 0; i < ledNum; i++) {
         uint32_t c=pixels.Color(255, 225, 225);
          pixels.setPixelColor(i, c);
        }
        pixels.show();
        delay(2000);
        pixels.clear();
    }
    Serial.println() ; // start new line of output
    pixels.clear();
    
  }
  
  // add some time and space between each output
  delay(2000);//100000
  Serial.println() ;
  Serial.println() ;
  
        }
  }
  if (millis() > 5000 && gps.charsProcessed() < 10)
      {
        Serial.println(F("No GPS detected: check wiring."));
        while(true);
      }

}

void displayInfo()
{ 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 3);
    Serial.print(F(","));
    Serial.println(gps.location.lng(), 3);
    //boardinfo("lat:" + String(latitudeBinary) + " lng:" +String(longitudeBinary),1);
   
  }
  else
  {
    Serial.print(F("INVALID"));
   
  }
}
