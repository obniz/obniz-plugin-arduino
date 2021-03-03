#include <obniz.h>
void setup() {
  Serial.begin(115200);
  obniz.start();
  obniz.pinReserve(12);
  pinMode(12, OUTPUT);
}
void loop() {
  digitalWrite(12, HIGH);
  delay(500);
  digitalWrite(12, LOW);
  delay(500);
}
