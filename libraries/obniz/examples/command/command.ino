#include <obniz.h>
void onCommand(uint8_t* data, uint16_t length){
  Serial.println("\nonCommand");
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

char message[20];
uint8_t counter = 0;
void loop() {
  sprintf(message,"obniz_message:%d",counter);
  counter++;

  if(!obniz.commandSend((uint8_t*)message,strlen(message))){
    Serial.printf("send message : %s\n",message);
  }
  delay(1000);
}