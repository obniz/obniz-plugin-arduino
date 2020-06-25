//
// Created by wami on 2020/05/13.
//

#ifndef INC_0_0_1_OBNIZ_H
#define INC_0_0_1_OBNIZ_H

#include <obniz_plugin.h>
#include "HardwareSerial.h"

typedef void(*CallbackEventFunction) (os_event_t event, uint8_t* data, uint16_t length);
typedef void(*CallbackCommandFunction) (uint8_t* data, uint16_t length);

class obniz_lib {
public:
    // obnizOS trigger
    int start();
    int start(HardwareSerial* serial);
    int start(char *id, char *key);
    int start(char *id, char *key, HardwareSerial* serial);
    void end();

    // obnizOS IO
    void pinReserve(uint8_t pin);
    void pinFree(uint8_t pin);

    // obnizOS data command
    void commandSend(uint8_t* data,uint16_t length);
    void commandReceive(CallbackCommandFunction commandCallBackFunction);

    // obnizOS event
    void onEvent(CallbackEventFunction eventCallBackFunction);

    //util
    const char* getId();
    const char* getOsVersion();
private:

};

extern obniz_lib obniz;
#endif //INC_0_0_1_OBNIZ_H
