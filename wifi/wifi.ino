#include <ESP8266WiFi.h>
const char *ssid = "coba"; //ganti nama hotspot
const char *pass = "mmmmmmmm";//ganti password
WiFiClient client;
void setup()
{
Serial.begin(115200);
delay(10);
Serial.print(" Connect to : ");
Serial.println(ssid);
WiFi.begin(ssid, pass);
while (WiFi.status() != WL_CONNECTED)
{
  delay(500);
  Serial.print("….");
}
Serial.print("\n");
Serial.print("IP address : ");
Serial.print(WiFi.localIP());
Serial.print("\n");
Serial.print("Connect to : ");
Serial.println(ssid);
}
void loop() { }
