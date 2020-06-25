#include <obniz.h>

/** Event type
    PLUGIN_EVENT_NETWORK_HARDWARE_CONNECTED = 0,
    PLUGIN_EVENT_NETWORK_CLOUD_CONNECTED,
    PLUGIN_EVENT_NETWORK_HARDWARE_DISCONNECTED,
    PLUGIN_EVENT_NETWORK_CLOUD_DISCONNECTED,

    PLUGIN_EVENT_NETWORK_WIFI_SCANNING = 10,
    PLUGIN_EVENT_NETWORK_WIFI_NOTFOUND,
    PLUGIN_EVENT_NETWORK_WIFI_CONNECTING,
    PLUGIN_EVENT_NETWORK_WIFI_SOFTAP_CONNECTED,
    PLUGIN_EVENT_NETWORK_WIFI_FAIL,

    PLUGIN_EVENT_FAIL = 20,

    PLUGIN_EVENT_OTA_START = 30,
    PLUGIN_EVENT_OTA_END,
    PLUGIN_EVENT_OTA_ERROR,
*/

void onEvent(os_event_t event, uint8_t* data, uint16_t length) {
  Serial.print("\narduino onEvent : ");
  Serial.println(event);
  switch (event) {
  case PLUGIN_EVENT_NETWORK_HARDWARE_CONNECTED:
    Serial.println("network Connected");
    break;
  case PLUGIN_EVENT_NETWORK_CLOUD_CONNECTED:
    Serial.println("cloud Connected");
    break;
  case PLUGIN_EVENT_NETWORK_HARDWARE_DISCONNECTED:
    Serial.println("network Disconnected");
    break;
  case PLUGIN_EVENT_NETWORK_CLOUD_DISCONNECTED:
    Serial.println("cloud Disconnected");
    break;
  }
}

void setup() {
  Serial.begin(115200);

  obniz.onEvent(onEvent);

  obniz.start();
}
void loop() {
}
