//
//  dummy.h
//  lifx-sdk-lib
//
//  Created by Apple on 6/30/15.
//  Copyright (c) 2015 LIFX. All rights reserved.
//

#ifndef lifx_sdk_lib_lifx_sdk_h
#define lifx_sdk_lib_lifx_sdk_h

#include "lifx-light-container.h"
#include <math.h>


void      lx_light_init();

void      lx_light_get_active();

void      lx_light_destroy();

char*     lx_light_get_name(uint8_t macAddress[8]);

bool      lx_light_get_on_off(uint8_t macAddress[8]);

float*    lx_light_get_color(uint8_t macAddress[8]);

void      lx_light_set_on_off(uint8_t macAddress[8], bool on_off, int delay);

void      lx_light_set_color(uint8_t macAddress[8], float *colors, int delay);

uint8_t** lx_light_get_macs();

int       lx_light_get_size();
#endif
