//
//  lifx-light-container.h
//  lifx-sdk-lib
//
//  Created by Apple on 6/30/15.
//  Copyright (c) 2015 LIFX. All rights reserved.
//

#ifndef lifx_sdk_lib_lifx_light_container_h
#define lifx_sdk_lib_lifx_light_container_h

#include "lifx-light.h"

typedef struct {
    uint8_t mac_addresses[MAX_NUMBER_MAC_ADDRESSES][8];
    lx_light_t* start;
    int size;
} lx_light_container_t;

#endif
