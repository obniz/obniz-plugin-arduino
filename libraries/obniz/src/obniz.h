//
// Created by wami on 2020/05/13.
//

#ifndef INC_0_0_1_OBNIZ_H
#define INC_0_0_1_OBNIZ_H

#include <obniz_plugin.h>
#include "HardwareSerial.h"

class obniz_lib {
public:
    int start();
    int start(HardwareSerial* serial);
    int start(char *id, char *key);
    int start(char *id, char *key, HardwareSerial* serial);
    void end();

private:

};

extern obniz_lib obniz;
#endif //INC_0_0_1_OBNIZ_H
