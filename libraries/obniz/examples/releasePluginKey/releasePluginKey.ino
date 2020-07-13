#include <obniz.h>
void setup() {
  Serial.begin(115200);
  obniz.setKey("obniz_plugin_key");
  obniz.start();
}

void loop() {
}
