//
// Created by wamis on 2020/05/13.
//

#include "obniz.h"
HardwareSerial* obniz_serial = NULL;
CallbackEventFunction _eventFunc = NULL;
CallbackCommandFunction _commandFunc = NULL;

int obniz_lib::start(){
    return this->start(NULL,NULL,&Serial);
}

int obniz_lib::start(HardwareSerial* serial){
    return this->start(NULL,NULL,serial);
}

int obniz_lib::start(char *id, char *key){
    return this->start(id,key,&Serial);
}

int obniz_lib::start(char *id, char *key, HardwareSerial* serial){
    obniz_serial = serial;
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

int obniz_lib::commandSend(uint8_t *data, uint16_t length) {
    return obniz_plugin_send(data,length);
}

void obniz_lib::commandReceive(CallbackCommandFunction callbackCommandFunction) {
    _commandFunc = callbackCommandFunction;
}

void obniz_lib::onEvent(CallbackEventFunction callbackEventFunction) {
    _eventFunc = callbackEventFunction;
}

const char* obniz_lib::getId() {
    return obniz_plugin_obniz_id();
}

const char* obniz_lib::getOsVersion() {
    return obniz_plugin_os_version();
}

bool obniz_lib::isRunning() {
  return obniz_plugin_is_running();
}

bool obniz_lib::isOnline() {
  return obniz_plugin_is_online();
}

// obnizOS Interface
void obniz_plugin_receive(uint8_t *command, uint16_t length){
    if(_commandFunc){
        _commandFunc(command,length);
    }
}

void obniz_plugin_console_print(const char *text, uint8_t length){
    if(obniz_serial) {
        obniz_serial->write((const uint8_t *) text, length);
    }
}

void obniz_plugin_console_input(uint8_t* text, uint32_t* length){
    if(obniz_serial) {
        *length = obniz_serial->available();
        if (*length != 0) {
            obniz_serial->read(text, *length);
        }
    }else{
        *length = 0;
    }
}

void obniz_plugin_event(os_event_t event, uint8_t* data, uint16_t length){
    if(_eventFunc){
        _eventFunc(event,data,length);
    }
}
obniz_lib obniz;