#include <obniz.h>
void setup() {
  Serial.begin(115200);
  obniz.start();
  Serial.println("obnizOS start");
  delay(60000);
  obniz.end();
  Serial.println("obnizOS end");
}
void loop() {
}
