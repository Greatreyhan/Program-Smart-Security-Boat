#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LED 14
#define Buzzer 12

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
int intValue = 0;

void setup(){
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
  
}

void loop(){
    if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0))
  {
    if (Firebase.getInt(fbdo, "/Kondisi/Kapal")) {
      if (fbdo.dataType() == "int") {         intValue = fbdo.intData();
        lcd.begin();
        lcd.clear();
        lcd.setCursor(0, 1);
        if(intValue == 0){
          lcd.print("Tidak Ada Kapal");
        }
        if(intValue == 1){
          lcd.print("Ada Kapal");
          digitalWrite(LED,HIGH);
        }
        if(intValue == 2){
          lcd.print("Kapal Nelayan");
          digitalWrite(LED,HIGH);
          digitalWrite(Buzzer,HIGH);
          delay(1000);
          digitalWrite(Buzzer,LOW);
        }
        if(intValue == 3){
          lcd.print("Kapal Musuh");
          digitalWrite(LED,HIGH);
          digitalWrite(Buzzer,HIGH);
          delay(400);
          digitalWrite(Buzzer,LOW);
          delay(400);
          digitalWrite(Buzzer,HIGH);
          delay(400);
          digitalWrite(Buzzer,LOW);
          delay(400);
        }
      }
    } else {
      Serial.println(fbdo.errorReason());
    }
  }
  digitalWrite(LED,LOW);
  digitalWrite(Buzzer,LOW);
}
