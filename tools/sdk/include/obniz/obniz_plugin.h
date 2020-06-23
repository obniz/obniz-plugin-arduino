//
// Created by wami on 2020/05/08.
//

#ifndef ESP32_FIRMWARE_OBNIZ_PLUGIN_H
#define ESP32_FIRMWARE_OBNIZ_PLUGIN_H
#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C" {
#endif
#define PLUGIN_EVENT_NETWORK_HARDWARE_CONNECTED 0
#define PLUGIN_EVENT_NETWORK_CLOUD_CONNECTED 1
#define PLUGIN_EVENT_NETWORK_HARDWARE_DISCONNECTED 2
#define PLUGIN_EVENT_NETWORK_CLOUD_DISCONNECTED 3
#define PLUGIN_EVENT_NETWORK_WIFI_SCANNING 10
#define PLUGIN_EVENT_NETWORK_WIFI_NOTFOUND 11
#define PLUGIN_EVENT_NETWORK_WIFI_CONNECTING 12
#define PLUGIN_EVENT_NETWORK_WIFI_SOFTAP_CONNECTED 13
#define PLUGIN_EVENT_NETWORK_WIFI_FAIL 14
#define PLUGIN_EVENT_FAIL 20
#define PLUGIN_EVENT_OTA_START 30
#define PLUGIN_EVENT_OTA_END 31
#define PLUGIN_EVENT_OTA_ERROR 32

// obniz start
void obniz_plugin_init();
void obniz_plugin_start();

//obnizId setup
int obniz_plugin_device_key(char *id, char *key);

// obniz end
void obniz_plugin_end();

//util
const char* obniz_plugin_os_version();
bool obniz_plugin_is_running();

//command
int obniz_plugin_send(uint8_t* data,uint16_t length);
extern void obniz_plugin_receive(uint8_t *command, uint32_t length);

//IO
void obniz_plugin_io_reserve(uint8_t io);
void obniz_plugin_io_free(uint8_t io);

//console
extern void obniz_plugin_console_print(const char *text, uint8_t length);
extern void obniz_plugin_console_input(uint8_t* text, uint8_t* length);

//event
extern void obniz_plugin_event(uint16_t command, uint8_t* data, uint16_t length);

#ifdef __cplusplus
}
#endif

#endif //ESP32_FIRMWARE_OBNIZ_PLUGIN_H
