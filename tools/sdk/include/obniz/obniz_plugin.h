//
// Created by wami on 2020/05/08.
//

#ifndef ESP32_FIRMWARE_OBNIZ_PLUGIN_H
#define ESP32_FIRMWARE_OBNIZ_PLUGIN_H

#ifdef __cplusplus
extern "C" {
#endif

void obniz_plugin_init();
void obniz_plugin_start();
int obniz_plugin_device_key(char *id, char *key);

#ifdef __cplusplus
}
#endif

#endif //ESP32_FIRMWARE_OBNIZ_PLUGIN_H
