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
