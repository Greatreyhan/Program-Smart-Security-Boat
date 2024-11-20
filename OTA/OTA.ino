#include <WiFi.h>
#include <HTTPClient.h>
#include <Update.h>

const char* ssid = "infinergy";
const char* password = "okeokeoke";
const char* serverUrl = "https://back.boatsecure676.vercel.app";

void updateFirmware() {
  WiFiClient client;
  HTTPClient http;

  Serial.print("Connecting to server: ");
  Serial.println(serverUrl);

  if (http.begin(client, serverUrl)) {
    int httpCode = http.GET();
    if (httpCode == HTTP_CODE_OK) {
      Serial.println("Updating firmware...");
      if (Update.begin(http.getSize())) {
        uint8_t buffer[1024];

        WiFiClient *stream = http.getStreamPtr();
        int len;
        while ((len = stream->readBytes(buffer, sizeof(buffer))) > 0) {
          if (Update.write(buffer, len) != len) {
            Serial.println("Firmware update failed");
            break;
          }
        }

        if (Update.end()) {
          Serial.println("Firmware update successful");
          if (Update.isFinished()) {
            ESP.restart();
          }
        } else {
          Serial.println("Firmware update failed");
        }
      } else {
        Serial.println("Unable to begin firmware update");
      }
    } else {
      Serial.print("Firmware update failed. Server returned HTTP code: ");
      Serial.println(httpCode);
    }

    http.end();
  } else {
    Serial.println("Unable to connect to server");
  }
}
void connectToWiFi() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());
}
void setup(){
  Serial.begin(115200);
  connectToWiFi();
  Serial.println("Starting OTA in 5 seconds");
  delay(5000);
  updateFirmware();
  }
  void loop(){
    }