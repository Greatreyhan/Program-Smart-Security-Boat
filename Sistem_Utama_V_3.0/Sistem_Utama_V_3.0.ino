#include <Wire.h>
#include <I2C_Anything.h>
#include <ESP8266WiFi.h>  
#include <FirebaseESP8266.h>

#define LEDRadar 14
#define LEDWarn 13
#define Buz 12

#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "infinergy"
#define WIFI_PASSWORD ""
#define API_KEY "AIzaSyAFUI6tT-8WtFapZyHU2yz0n2Zsa5AWUJk"
#define DATABASE_URL "hoverconnectsystem-default-rtdb.firebaseio.com" 
#define USER_EMAIL "maulanareyhan252@gmail.com"
#define USER_PASSWORD "Maulana252"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0; 
int count = 0;

const char *ssid = "coba"; 
const char *password = "mmmmmmmm";  

bool statusKapal = false;

volatile float radar;
void setup()
{
    pinMode(LEDRadar,OUTPUT);
    pinMode(LEDWarn, OUTPUT);
    pinMode(Buz, OUTPUT);
    Serial.begin(115200);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED)
    {
      Serial.print(".");
      delay(300);
    }
    Serial.println();
    Serial.print("Connected with IP: ");
    Serial.println(WiFi.localIP());
    Serial.println();
  
    Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
    config.api_key = API_KEY;
    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;
    config.database_url = DATABASE_URL;
    config.token_status_callback = tokenStatusCallback;
    Firebase.begin(&config, &auth);
    
    Wire.begin(D1, D2); 
}

void loop()
{
  Wire.requestFrom(8, 4); // reqeust 6 bytes from salve Uno #8
  I2C_readAnything (radar);
  if(radar >= 1){
    
    // Menyalakan LED & buz
    digitalWrite(LEDRadar, HIGH);
    digitalWrite(Buz, HIGH);
    delay(1000);
    digitalWrite(Buz, LOW);
    
    // Update data ke firebase
    if (Firebase.setInt(fbdo, "/Kondisi/Kapal",1)) {
      Serial.println("Ada Kapal");
    } else {
      Serial.println(fbdo.errorReason());
    }
    
    // Menyalakan hotspot
    WiFi.softAP(ssid, password); 
    Serial.print("Connecting");
    Serial.print("Access Point \"");
    Serial.print(ssid);
    Serial.println("\" started");
    Serial.print("IP address:\t");
    Serial.println(WiFi.softAPIP());   
    for(uint32_t i = 0; i <= 10; i++){
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
      
     // Menyalakan led Warn & Buzzer
     digitalWrite(LEDRadar, LOW);
     digitalWrite(LEDWarn, HIGH); 
     digitalWrite(Buz, HIGH);  
     delay(1000);
     digitalWrite(Buz, LOW);  
      
      if (Firebase.setInt(fbdo, "/Kondisi/Kapal",2)) {
        Serial.println("Kapal Nelayan");
      } else {
        Serial.println(fbdo.errorReason());
      }
      statusKapal = false;
      WiFi.softAPdisconnect();
      delay(15000);
    }
    else{
      
       if (Firebase.setInt(fbdo, "/Kondisi/Kapal",3)) {
        Serial.println("Kapal Musuh");
      } else {
        Serial.println(fbdo.errorReason());
      }
      // Peringatan
      digitalWrite(LEDRadar, HIGH);
      digitalWrite(Buz, HIGH);
      delay(1000);
      digitalWrite(LEDRadar, LOW);
      digitalWrite(Buz, LOW);
      delay(1000);
      digitalWrite(LEDRadar, HIGH);
      digitalWrite(Buz, HIGH);
      delay(1000);
      digitalWrite(LEDRadar, LOW);
      digitalWrite(Buz, LOW);
      delay(1000);
      digitalWrite(LEDRadar, HIGH);
      digitalWrite(Buz, HIGH);
      delay(1000);
      digitalWrite(LEDRadar, LOW);
      digitalWrite(Buz, LOW);
      delay(1000);
      digitalWrite(LEDRadar, HIGH);
      digitalWrite(Buz, HIGH);
      delay(1000);
      digitalWrite(LEDRadar, LOW);
      digitalWrite(Buz, LOW);
      delay(8000);
      
    }
    if(radar >=1){
      digitalWrite(LEDRadar,HIGH);
    }
    else{
      digitalWrite(LEDRadar,LOW);
    }
  }
  else{
    digitalWrite(LEDRadar,LOW);
    digitalWrite(LEDWarn, LOW); 
    if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)){
    if (Firebase.setInt(fbdo, "/Kondisi/Kapal",0)) {
      Serial.println("Tidak Ada Kapal");
    } else {
      Serial.println(fbdo.errorReason());
    }
  }  
  }
}
