//
// Created by wami on 2020/05/08.
//

#ifndef ESP32_FIRMWARE_OBNIZ_PLUGIN_H
#define ESP32_FIRMWARE_OBNIZ_PLUGIN_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

void obniz_plugin_init();
void obniz_plugin_start();
const char* obniz_plugin_os_version();
int obniz_plugin_device_key(char *id, char *key);
int obniz_plugin_send(uint8_t* data,uint16_t length);
extern void obniz_plugin_receive(uint8_t *command, uint32_t length);
void obniz_plugin_io_reserve(uint8_t io);
void obniz_plugin_io_free(uint8_t io);
void obniz_log(char * message);
#ifdef __cplusplus
}
#endif

#endif //ESP32_FIRMWARE_OBNIZ_PLUGIN_H
