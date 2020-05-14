//
// Created by wamis on 2020/05/13.
//

#include "obniz.h"

int obniz_lib::start(){
    obniz_plugin_init();
    obniz_plugin_start();
    return 0;
}

int obniz_lib::start(char *id, char *key){
    obniz_plugin_init();
    int rst = obniz_plugin_device_key(id,key);
    obniz_plugin_start();
    return rst;
}

obniz_lib obniz;