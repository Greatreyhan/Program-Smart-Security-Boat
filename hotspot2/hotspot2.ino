#include <ESP8266WiFi.h>
// include plain C library

#define YOUR_WIFI_SSID "coba"
#define YOUR_WIFI_PASSWD "mmmmmmmm"

boolean waitingDHCP=false;
char last_mac[18];

// Manage incoming device connection on ESP access point
void onNewStation(WiFiEventSoftAPModeStationConnected sta_info) {
  Serial.println("New Station :");
  sprintf(last_mac,"%02X:%02X:%02X:%02X:%02X:%02X", MAC2STR(sta_info.mac));
  Serial.printf("MAC address : %s\n",last_mac);
  Serial.printf("Id : %d\n", sta_info.aid);
  waitingDHCP=true;
}

void setup() { 

  static WiFiEventHandler e1;

  Serial.begin(115200);
  Serial.println("Ready");
  Serial.println();
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(YOUR_WIFI_SSID, YOUR_WIFI_PASSWD);

  // Event subscription
  e1 = WiFi.onSoftAPModeStationConnected(onNewStation);
}

void loop() {

  if (waitingDHCP) {
    String cb;
    if (deviceIP(last_mac,cb)) {
      Serial.println("Ip address :");
      Serial.println(cb); //do something
    } else {
      Serial.println("Problem during ip address request :");
      Serial.println(cb); //do something else
    }
  }

  delay(2000);
}

boolean deviceIP(char* mac_device, String &cb) {

  struct station_info *station_list = wifi_softap_get_station_info();

  while (station_list != NULL) {
    char station_mac[18] = {0}; sprintf(station_mac, "%02X:%02X:%02X:%02X:%02X:%02X", MAC2STR(station_list->bssid));
    String station_ip = IPAddress((&station_list->ip)->addr).toString();

    if (strcmp(mac_device,station_mac)==0) {
      waitingDHCP=false;
      cb = station_ip;
      return true;
    } 

    station_list = STAILQ_NEXT(station_list, next);
  }

  wifi_softap_free_station_info();
  cb = "DHCP not ready or bad MAC address";
  return false;
}
