//
//  dummy.c
//  lifx-sdk-lib
//
//  Created by Apple on 6/30/15.
//  Copyright (c) 2015 LIFX. All rights reserved.
//

#include <stdio.h>
#include "lifx-sdk.h"

void extern init(lx_light_container_t *lightCollection);
void extern setPower(lx_light_t *light, bool on_off, int delay);
void extern setColor(lx_light_t *light, float* color, int delay);
void extern deinit(lx_light_container_t *lightCollection);
void extern getActive(lx_light_container_t* lightCollection);

lx_light_container_t* lightContainer;
bool compare(lx_light_t* light, uint8_t macAddress[8]) {
    int i = 5;
    for (; i >= 0; i--) {
        if (light->target[i] != macAddress[i])
            return false;
    }
    return true;
}

lx_light_t* find(uint8_t macAddress[8]){
    lx_light_t *currentLight = lightContainer->start;
    do {
        if (compare(currentLight, macAddress)) {
            return currentLight;
        }
        currentLight = currentLight->next;
    } while (currentLight->next != NULL);
    return NULL;
}

void lx_light_init(l) {
    lightContainer = malloc(sizeof(lx_light_container_t));
    init(lightContainer);
}

void lx_light_get_active() {
    getActive(lightContainer);
}

void lx_light_destroy(){
    deinit(lightContainer);
    free(lightContainer);
}

int lx_light_get_size() {
    return lightContainer->size;
}
uint8_t** lx_light_get_macs() {
    return lightContainer->mac_addresses;
}
char* lx_light_get_name(uint8_t macAddress[8]){
    lx_light_t* light = find(macAddress);
    if (light == NULL)
        return NULL;
    return light->label;
}

bool lx_light_get_on_off(uint8_t macAddress[8]){
    lx_light_t* light = find(macAddress);
    if (light == NULL)
        return NULL;
    return light->on_off;
}

float* lx_light_get_color(uint8_t macAddress[8]){
    lx_light_t* light = find(macAddress);
    if (light == NULL)
        return NULL;
    float color[4] = {light->color.hue, light->color.saturation, light->color.brightness, light->color.kelvin};
    return color;
}

void lx_light_set_on_off(uint8_t macAddress[8], bool on_off, int delay){
    lx_light_t* light = find(macAddress);
    if (light == NULL)
        return;
    setPower(light, on_off, delay);
    light->on_off = on_off;
}

void lx_light_set_color(uint8_t macAddress[8], float *colors, int delay){
    lx_light_t* light = find(macAddress);
    if (light == NULL)
        return;
    setColor(light, colors, delay);
    light->color.hue = colors[0];
    light->color.saturation = colors[1];
    light->color.brightness = colors[2];
    light->color.kelvin = colors[3];
}