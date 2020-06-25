#include <obniz.h>
#define LED_IO 12

bool onlineFlg = false;

void onEvent(os_event_t event, uint8_t* data, uint16_t length) {
  switch (event) {
  case PLUGIN_EVENT_NETWORK_CLOUD_CONNECTED:
    Serial.println("cloud Connected");
    onlineFlg = true;
    break;
  case PLUGIN_EVENT_NETWORK_CLOUD_DISCONNECTED:
    Serial.println("cloud Disconnected");
    onlineFlg = false;
    break;
  case PLUGIN_EVENT_NETWORK_HARDWARE_CONNECTED:
  case PLUGIN_EVENT_NETWORK_HARDWARE_DISCONNECTED:
  case PLUGIN_EVENT_NETWORK_WIFI_SCANNING:
  case PLUGIN_EVENT_NETWORK_WIFI_NOTFOUND:
  case PLUGIN_EVENT_NETWORK_WIFI_CONNECTING:
  case PLUGIN_EVENT_NETWORK_WIFI_SOFTAP_CONNECTED:
  case PLUGIN_EVENT_NETWORK_WIFI_FAIL:
  case PLUGIN_EVENT_FAIL:
  case PLUGIN_EVENT_OTA_START:
  case PLUGIN_EVENT_OTA_END:
  case PLUGIN_EVENT_OTA_ERROR:
    break;
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("online led ok start!");

  obniz.onEvent(onEvent);

  obniz.start(NULL);

  pinMode(LED_IO, OUTPUT);
}
void loop() {
  digitalWrite(LED_IO, onlineFlg);
}
