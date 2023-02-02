#include <ESP8266WiFi.h>        
const char *ssid = "coba"; 
const char *password = "mmmmmmmm";   
void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');
WiFi.softAP(ssid, password);      
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");
Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());   
  Serial.println(WiFi.status());      
}
void loop() { }
