#pragma once

#include <stddef.h>

// Size of a field inside a raw level 0 frame
#define lx_protocol_frame_field_sizeof(m) (sizeof(((lx_frame_address_t *)NULL)->m))

// Size of a complete message inside a level 1 protocol frame
#define lx_protocol_sizeof(s)             (offsetof(lx_protocol_t, payload) + sizeof(s))

// Size of a field inside a level 1 protocol message
#define lx_protocol_field_sizeof(s, m)    (sizeof(((lx_protocol_t *)NULL)->payload.s.m))
