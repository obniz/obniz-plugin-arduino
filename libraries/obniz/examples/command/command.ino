#include <obniz.h>
void onCommand(uint8_t* data, uint16_t length){
  Serial.println("onCommand");
  Serial.write(data,length);
  Serial.println("\nEnd onCommand");
}

void setup() {
  Serial.begin(115200);

  obniz.commandReceive(onCommand);
  obniz.start();

  while(!obniz.getId());
  Serial.printf("obnizID : %s\n",obniz.getId());
}

char buff[100];
uint8_t counter = 0;
void loop() {
  sprintf(buff,"obniz_message:%d",counter);
  counter++;

  if(!obniz.commandSend((uint8_t*)buff,strlen(buff))){
    Serial.printf("send message : %s\n",buff);
  }
}
