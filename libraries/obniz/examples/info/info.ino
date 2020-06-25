#include <obniz.h>
void setup() {
  Serial.begin(115200);
  obniz.start();

  while(!obniz.getId());
  Serial.printf("obnizID : %s\n",obniz.getId());
  Serial.printf("obnizOS : %s\n",obniz.getOsVersion());
}
void loop() {
}
