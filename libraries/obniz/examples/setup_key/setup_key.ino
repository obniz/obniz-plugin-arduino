#include <obniz.h>
void setup() {
  Serial.begin(115200);
  obniz.start("obniz_id","key");
}
void loop() {
}
