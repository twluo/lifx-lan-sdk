//
//  lfx-light.h
//  lifx-sdk-lib
//
//  Created by Apple on 6/30/15.
//  Copyright (c) 2015 LIFX. All rights reserved.
//

#ifndef lifx_sdk_lib_lifx_light_h
#define lifx_sdk_lib_lifx_light_h

#include "lifx-udp.h"
#include <stdbool.h>

#define MAX_NUMBER_MAC_ADDRESSES 100

typedef struct {
    float hue;
    float saturation;
    float brightness;
    float kelvin;
} lx_light_color;

typedef struct lx_light_t{
    char label[256];
    uint8_t target[8];
    struct sockaddr_in addr;
    lx_light_color color;
    bool on_off;
    struct lx_light_t *next;
} lx_light_t;

#endif
