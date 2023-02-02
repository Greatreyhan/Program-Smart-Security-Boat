#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiServerSecure.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <ESP8266WebServerSecure.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266Ping.h>
#include <my_lib_COMMON.h>
#include <my_lib_Esp8266_MCU_ONLY.h>


extern "C" {
  #include<user_interface.h>
}


#define PORT 80
const String MODULE_HOSTNAME = "numberone";
const char* ssid =  "okeokeoke";
const char* pass =  "okeokeoke";


ESP8266WebServer server(PORT);


bool SCAN_NETWORKS = false;
bool CONNECT_TO_NETWORK = true;
bool RUN_WEBSERVER = true;
bool CHANGE_HOSTNAME = false;

void setup() 
{
  Serial.begin(9600);

  Serial.println("\n");

  if (CONNECT_TO_NETWORK)
  {
    if (CONNECT_TO_SSID_AND_OUTPUT_SERIAL(ssid, pass))
    {
      IPs_TO_SERIAL(PORT);
    }
  }

  if (RUN_WEBSERVER)
  {
    /*server.on("/list", HTTP_GET, printDirectory);
    server.on("/edit", HTTP_DELETE, handleDelete);
    server.on("/edit", HTTP_PUT, handleCreate);
    server.on("/edit", HTTP_POST, []()
    {
      returnOK();
    }, handleFileUpload);*/
    server.onNotFound(handleNotFound);

    Serial.print("Activating Webserver... ");
    server.begin();
    Serial.println("OK!");
  }
}


void loop() 
{      
  if (RUN_WEBSERVER)
  {
    server.handleClient();
  }
}

void handleNotFound()
{
  Serial.println("New client with IP:" + IP + " and MAC: " + MAC); <==== client's IP and MAC here
  Serial.println("handleNotFound");
  Serial.println("Client status:");
  if (hasSD && loadFromSdCard(server.uri()))
  {
    return;
  }
  String message = "File not Detected\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " NAME:" + server.argName(i) + "\n VALUE:" + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  Serial.print("Sent to client:");
  Serial.println(message);

  Serial.println("Connection terminated.");
}
