//
// Created by wamis on 2020/05/13.
//

#include "obniz.h"
HardwareSerial* obniz_serial = NULL;
CallbackEventFunction _eventFunc = NULL;
CallbackCommandFunction _commandFunc = NULL;

int obniz_lib::start(){
    return this->start(NULL,&Serial);
}

int obniz_lib::start(HardwareSerial* serial){
    return this->start(NULL,serial);
}

int obniz_lib::start(char *key, HardwareSerial* serial){
    obniz_serial = serial;
    obniz_plugin_init();
    int rst = 0;
    if(key != NULL) {
        char obniz_id[32];
        char obniz_key[255];
        int err;
        /* id と private keyに分離 */
        /* format: 00000000&01234567789ABCDEF */
        uint16_t index = 0;
        while (strlen(key) >= index) {
            if ('0' <= key[index] && key[index] <= '9') {
                obniz_id[index] = key[index];
                index++;
            } else if (key[index] == '&') {
                obniz_id[index] = '\0';
                index++;
                break;
            } else {
                err = 1;
                break;
            }
        }
        if (err || index < 9) {
            return -1; // invalid obniz id
        }
        uint16_t head = 0;
        while (strlen(key) >= index)
        {
            if (('0' <= key[index] && key[index] <= '9') || ('A' <= key[index] && key[index] <= 'F') ||
                ('a' <= key[index] && key[index] <= 'z')) {
                obniz_key[head] = key[index];
                index++;
                head++;
            } else if (key[index] == '\0') {
                obniz_key[head] = '\0';
                break;
            } else {
                err = 1;
                break;
            }
        }
        if (err || head < 1 || head % 2 != 0){
            return -2;// invalid obniz devicekey
        }
        rst = obniz_plugin_device_key(obniz_id,obniz_key);
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

bool obniz_lib::startSettingPage(){
    return obniz_plugin_init_setting_page();
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

void obniz_lib::pinReserve(uint8_t pin) {
  obniz_plugin_io_reserve(pin);
}

void obniz_lib::pinFree(uint8_t pin) {
  obniz_plugin_io_free(pin);
}

// obnizOS app key
bool obniz_lib::setKey(char *key_50_text) {
  return obniz_plugin_key(key_50_text);
}

// obnizOS Interface
void obniz_plugin_receive(uint8_t *command, uint16_t length){
    if(_commandFunc){
        _commandFunc(command,length);
    }
}

void obniz_plugin_console_print(const char *text, uint32_t length){
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