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
typedef enum {
    PLUGIN_EVENT_NETWORK_HARDWARE_CONNECTED = 0,
    PLUGIN_EVENT_NETWORK_CLOUD_CONNECTED,
    PLUGIN_EVENT_NETWORK_HARDWARE_DISCONNECTED,
    PLUGIN_EVENT_NETWORK_CLOUD_DISCONNECTED,

    PLUGIN_EVENT_NETWORK_WIFI_SCANNING = 10,
    PLUGIN_EVENT_NETWORK_WIFI_NOTFOUND,
    PLUGIN_EVENT_NETWORK_WIFI_CONNECTING,
    PLUGIN_EVENT_NETWORK_WIFI_SOFTAP_CONNECTED,
    PLUGIN_EVENT_NETWORK_WIFI_FAIL,

    PLUGIN_EVENT_FAIL = 20,

    PLUGIN_EVENT_OTA_START = 30,
    PLUGIN_EVENT_OTA_END,
    PLUGIN_EVENT_OTA_ERROR,
} os_event_t;

// obniz start
void obniz_plugin_init();
void obniz_plugin_start();

//obnizId setup
int obniz_plugin_device_key(char *id, char *key);

// obniz end
void obniz_plugin_end();

//util
const char* obniz_plugin_os_version();
const char* obniz_plugin_obniz_id();
bool obniz_plugin_is_running();

//command
int obniz_plugin_send(uint8_t* data,uint16_t length);
extern void obniz_plugin_receive(uint8_t *command, uint16_t length);

//IO
void obniz_plugin_io_reserve(uint8_t io);
void obniz_plugin_io_free(uint8_t io);

//console
extern void obniz_plugin_console_print(const char *text, uint8_t length);
extern void obniz_plugin_console_input(uint8_t* text, uint32_t* length);

//event
extern void obniz_plugin_event(os_event_t event, uint8_t* data, uint16_t length);

#ifdef __cplusplus
}
#endif

#endif //ESP32_FIRMWARE_OBNIZ_PLUGIN_H
