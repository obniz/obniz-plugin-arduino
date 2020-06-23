//
// Created by wamis on 2020/05/13.
//

#include "obniz.h"
HardwareSerial* obniz_serial = NULL;
int obniz_lib::start(){
    return this->start(NULL,NULL,NULL);
}

int obniz_lib::start(HardwareSerial* serial){
    return this->start(NULL,NULL,serial);
}

int obniz_lib::start(char *id, char *key){
    return this->start(id,key,NULL);
}

int obniz_lib::start(char *id, char *key, HardwareSerial* serial){
    if(serial != NULL) {
        obniz_serial = serial;
    }else{
        obniz_serial = &Serial;
    }
    obniz_plugin_init();
    int rst = 0;
    if(id != NULL && key != NULL){
        rst = obniz_plugin_device_key(id,key);
    }
    obniz_plugin_start();
    return rst;
}

void obniz_lib::end() {
    obniz_plugin_end();
}

void obniz_plugin_receive(uint8_t *command, uint32_t length){

}

void obniz_plugin_console_print(const char *text, uint8_t length){
    obniz_serial->write((const uint8_t*)text,length);
}

void obniz_plugin_console_input(uint8_t* text, uint8_t* length){
    *length = obniz_serial->available();
    if(*length != 0){
        obniz_serial->read(text,*length);
    }
}

void obniz_plugin_event(uint16_t command, uint8_t* data, uint16_t length){
    obniz_serial->printf("\nevent : %d",command);
}
obniz_lib obniz;