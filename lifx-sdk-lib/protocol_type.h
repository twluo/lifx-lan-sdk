#pragma once

#ifdef __cplusplus
  extern "C" {
#endif

// Generated code!

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/*
  lx_protocol_device
*/

typedef enum lx_protocol_device_service_t {
    LX_PROTOCOL_DEVICE_SERVICE_UDP = 1
} lx_protocol_device_service_t;

#define LX_PROTOCOL_DEVICE_TYPES \
  X(LX_PROTOCOL_DEVICE_STATE_SERVICE, lx_protocol_device_state_service) \
  X(LX_PROTOCOL_DEVICE_STATE_HOST_INFO, lx_protocol_device_state_host_info) \
  X(LX_PROTOCOL_DEVICE_STATE_HOST_FIRMWARE, lx_protocol_device_state_host_firmware) \
  X(LX_PROTOCOL_DEVICE_STATE_WIFI_INFO, lx_protocol_device_state_wifi_info) \
  X(LX_PROTOCOL_DEVICE_STATE_WIFI_FIRMWARE, lx_protocol_device_state_wifi_firmware) \
  X(LX_PROTOCOL_DEVICE_SET_POWER, lx_protocol_device_set_power) \
  X(LX_PROTOCOL_DEVICE_STATE_POWER, lx_protocol_device_state_power) \
  X(LX_PROTOCOL_DEVICE_SET_LABEL, lx_protocol_device_set_label) \
  X(LX_PROTOCOL_DEVICE_STATE_LABEL, lx_protocol_device_state_label) \
  X(LX_PROTOCOL_DEVICE_STATE_VERSION, lx_protocol_device_state_version) \
  X(LX_PROTOCOL_DEVICE_STATE_INFO, lx_protocol_device_state_info) \
  X(LX_PROTOCOL_DEVICE_ECHO_REQUEST, lx_protocol_device_echo_request) \
  X(LX_PROTOCOL_DEVICE_ECHO_RESPONSE, lx_protocol_device_echo_response)

#pragma pack(push, 1)
typedef struct lx_protocol_device_state_service_t {
  uint8_t  service;
  uint32_t port;
} lx_protocol_device_state_service_t;
      
typedef struct lx_protocol_device_state_host_info_t {
  float    signal;
  uint32_t tx;
  uint32_t rx;
  int16_t  mcu_temperature;
} lx_protocol_device_state_host_info_t;

typedef struct lx_protocol_device_state_host_firmware_t {
  uint64_t build;
  uint64_t install;
  uint32_t version;
} lx_protocol_device_state_host_firmware_t;

typedef struct lx_protocol_device_state_wifi_info_t {
  float    signal;
  uint32_t tx;
  uint32_t rx;
  int16_t  mcu_temperature;
} lx_protocol_device_state_wifi_info_t;

typedef struct lx_protocol_device_state_wifi_firmware_t {
  uint64_t build;
  uint64_t install;
  uint32_t version;
} lx_protocol_device_state_wifi_firmware_t;

typedef struct lx_protocol_device_set_power_t {
  uint16_t level;
} lx_protocol_device_set_power_t;

typedef struct lx_protocol_device_state_power_t {
  uint16_t level;
} lx_protocol_device_state_power_t;

typedef struct lx_protocol_device_set_label_t {
  uint8_t  label[32];
} lx_protocol_device_set_label_t;

typedef struct lx_protocol_device_state_label_t {
  uint8_t  label[32];
} lx_protocol_device_state_label_t;

typedef struct lx_protocol_device_state_version_t {
  uint32_t vendor;
  uint32_t product;
  uint32_t version;
} lx_protocol_device_state_version_t;

typedef struct lx_protocol_device_state_info_t {
  uint64_t time;
  uint64_t uptime;
  uint64_t downtime;
} lx_protocol_device_state_info_t;

typedef struct lx_protocol_device_echo_request_t {
  uint8_t  payload[64];
} lx_protocol_device_echo_request_t;

typedef struct lx_protocol_device_echo_response_t {
  uint8_t  payload[64];
} lx_protocol_device_echo_response_t;
#pragma pack(pop)

/*
  lx_protocol_light
*/

#define LX_PROTOCOL_LIGHT_TYPES \
  X(LX_PROTOCOL_LIGHT_HSBK, lx_protocol_light_hsbk) \
  X(LX_PROTOCOL_LIGHT_SET_COLOR, lx_protocol_light_set_color) \
  X(LX_PROTOCOL_LIGHT_SET_POWER, lx_protocol_light_set_power) \
  X(LX_PROTOCOL_LIGHT_STATE_POWER, lx_protocol_light_state_power) \
  X(LX_PROTOCOL_LIGHT_STATE, lx_protocol_light_state) \

#pragma pack(push, 1)
typedef struct lx_protocol_light_hsbk_t {
  uint16_t hue;
  uint16_t saturation;
  uint16_t brightness;
  uint16_t kelvin;
} lx_protocol_light_hsbk_t;

typedef struct lx_protocol_light_set_color_t {
  uint8_t  stream;
  lx_protocol_light_hsbk_t color;
  uint32_t duration;
} lx_protocol_light_set_color_t;

typedef struct lx_protocol_light_set_power_t {
  uint16_t level;
  uint32_t duration;
} lx_protocol_light_set_power_t;

typedef struct lx_protocol_light_state_power_t {
  uint16_t level;
} lx_protocol_light_state_power_t;

typedef struct lx_protocol_light_state_t {
  lx_protocol_light_hsbk_t color;
  int16_t  dim;
  uint16_t power;
  uint8_t  label[32];
  uint64_t tags;
} lx_protocol_light_state_t;
#pragma pack(pop)

/*
  lx_protocol
*/

typedef enum lx_protocol_type_t {
  LX_PROTOCOL_DEVICE_GET_SERVICE = 2,
  LX_PROTOCOL_DEVICE_STATE_SERVICE = 3,
  LX_PROTOCOL_DEVICE_GET_HOST_INFO = 12,
  LX_PROTOCOL_DEVICE_STATE_HOST_INFO = 13,
  LX_PROTOCOL_DEVICE_GET_HOST_FIRMWARE = 14,
  LX_PROTOCOL_DEVICE_STATE_HOST_FIRMWARE = 15,
  LX_PROTOCOL_DEVICE_GET_WIFI_INFO = 16,
  LX_PROTOCOL_DEVICE_STATE_WIFI_INFO = 17,
  LX_PROTOCOL_DEVICE_GET_WIFI_FIRMWARE = 18,
  LX_PROTOCOL_DEVICE_STATE_WIFI_FIRMWARE = 19,
  LX_PROTOCOL_DEVICE_GET_POWER = 20,
  LX_PROTOCOL_DEVICE_SET_POWER = 21,
  LX_PROTOCOL_DEVICE_STATE_POWER = 22,
  LX_PROTOCOL_DEVICE_GET_LABEL = 23,
  LX_PROTOCOL_DEVICE_SET_LABEL = 24,
  LX_PROTOCOL_DEVICE_STATE_LABEL = 25,
  LX_PROTOCOL_DEVICE_GET_VERSION = 32,
  LX_PROTOCOL_DEVICE_STATE_VERSION = 33,
  LX_PROTOCOL_DEVICE_GET_INFO = 34,
  LX_PROTOCOL_DEVICE_STATE_INFO = 35,
  LX_PROTOCOL_DEVICE_ACKNOWLEDGEMENT = 45,
  LX_PROTOCOL_DEVICE_ECHO_REQUEST = 58,
  LX_PROTOCOL_DEVICE_ECHO_RESPONSE = 59,
  LX_PROTOCOL_LIGHT_GET = 101,
  LX_PROTOCOL_LIGHT_SET_COLOR = 102,
  LX_PROTOCOL_LIGHT_STATE = 107,
  LX_PROTOCOL_LIGHT_GET_POWER = 116,
  LX_PROTOCOL_LIGHT_SET_POWER = 117,
  LX_PROTOCOL_LIGHT_STATE_POWER = 118,
} lx_protocol_type_t;


#ifdef __cplusplus
  }
#endif
