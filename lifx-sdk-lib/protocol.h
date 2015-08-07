#pragma once

#include "frame.h"
#include "protocol_type.h"
#include "protocol_sizes.h"

/*

Level 2 - LIFX Protocol.

The LIFX message protocol.

+------+------------+--------+--------+----------+-----------+----------+------+-----------+---------+
| size | descriptor | source | target | reserved | routing   | reserved | type | reserved  | payload |
+------+------------+--------+--------+------+-----------+----------+------+-----------+---------+

*/
#pragma pack(push, 1)
typedef struct lx_protocol_t {
  LX_FRAME_ADDRESS_FIELDS
  uint64_t reserved64;
  uint16_t type;
  uint16_t reserved16;
  union {
    #define X(constant, name) name ## _t name;
    LX_PROTOCOL_DEVICE_TYPES \
    LX_PROTOCOL_LIGHT_TYPES
    #undef X
  } payload;
} lx_protocol_t;
#pragma pack(pop)
