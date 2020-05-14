#include <obniz.h>
void setup() {
  obniz.start();
  pinMode(12, OUTPUT);
}
void loop() {
  digitalWrite(12, HIGH);
  delay(500);
  digitalWrite(12, LOW);
  delay(500);
}
