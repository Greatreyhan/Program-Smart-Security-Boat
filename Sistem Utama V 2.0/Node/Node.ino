#include <Wire.h>
#include <I2C_Anything.h>
#include <ESP8266WiFi.h>  

#define LEDRadar 13

const char *ssid = "coba"; 
const char *password = "mmmmmmmm";  

bool statusKapal = false;

volatile float radar;
void setup()
{
  Serial.begin(115200);
  Wire.begin(D1, D2); 
}

void loop()
{
  Wire.requestFrom(8, 4); // reqeust 6 bytes from salve Uno #8
  I2C_readAnything (radar);
  if(radar >= 1){
    // Update data ke firebase

    // Menyalakan hotspot
    WiFi.softAP(ssid, password); 
    Serial.print("Connecting");
    Serial.print("Access Point \"");
    Serial.print(ssid);
    Serial.println("\" started");
    Serial.print("IP address:\t");
    Serial.println(WiFi.softAPIP());   
    for(uint32_t i = 0; i <= 60; i++){
      Serial.print(".");
      
      // Cek apakah ada yang konek
      if(WiFi.softAPgetStationNum() >= 1){
        Serial.println(WiFi.status());
        statusKapal = true;
        break;
      }
      delay(1000);
    } 
    if(statusKapal){
      Serial.print("Kapal Nelayan");
      statusKapal = false;
      WiFi.softAPdisconnect();
    }
    else{
      Serial.print("Kapal Musuh");
    }
    if(radar >=1){
      digitalWrite(LEDRadar,HIGH);
    }
    else{
      digitalWrite(LEDRadar,LOW);
    }
  }
}
