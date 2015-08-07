//
//  lifx-light.c
//  lifx-sdk-lib
//
//  Created by Apple on 6/30/15.
//  Copyright (c) 2015 LIFX. All rights reserved.
//

#include <stdio.h>
#include "lifx-light.h"
#include "protocol.h"

extern void udpSendMsg(UDPSocket *udp, lx_protocol_t header, struct sockaddr_in sndAddr);

extern void udpRecvMsg(UDPSocket *udp);

extern UDPSocket unicast_udp_socket;

bool compareMacs(uint8_t mac[8], uint8_t macAddress[8]) {
    int i = 5;
    for (; i >= 0; i--) {
        if (mac[i] != macAddress[i])
            return false;
    }
    return true;
}

void getName(lx_light_t *light) {
    lx_protocol_t header;
    header.protocol = 1024;
    header.addressable = 1;
    header.tagged = 1;
    header.origin = 0;
    header.source = 1;
    for (int i = 0; i < 8; i++)
        header.target[i] = 0;
    header.ack_required = 0;
    header.res_required = 0;
    header.sequence = 0;
    header.reserved64 = 0;
    for(int i = 0; i < 6; i++) {
        header.reserved[i] = 0;
    }
    header.type = LX_PROTOCOL_LIGHT_GET;
    header.size = offsetof(lx_protocol_t, payload);
    lx_protocol_t *msg;
    int counter = 0;
    while(counter < 5) {
        counter++;
        udpSendMsg(&unicast_udp_socket, header, light->addr);
        udpRecvMsg(&unicast_udp_socket);
        msg = (lx_protocol_t *) (unicast_udp_socket.buffer);
        if (msg->type == LX_PROTOCOL_LIGHT_STATE && compareMacs(msg->target, light->target)) {
            memset(light->label, '\0', sizeof(light->label));
            strcpy(light->label, msg->payload.lx_protocol_light_state.label);
            printf("Original name is %c and copied name is %s\n", *msg->payload.lx_protocol_light_state.label, light->label);
            light->color.hue        = (float)(msg->payload.lx_protocol_light_state.color.hue)/0xFFFF * 360;
            light->color.saturation = (float)msg->payload.lx_protocol_light_state.color.saturation/0xFFFF;
            light->color.brightness = (float)msg->payload.lx_protocol_light_state.color.brightness/0xFFFF;
            light->color.kelvin     = msg->payload.lx_protocol_light_state.color.kelvin;
/*            printf("%f %f %f %f\n", light->color.hue, light->color.saturation, light->color.brightness, light->color.kelvin);
            printf("%f %f %f %f\n", msg->payload.lx_protocol_light_state.color.hue,msg->payload.lx_protocol_light_state.color.saturation,msg->payload.lx_protocol_light_state.color.brightness,msg->payload.lx_protocol_light_state.color.kelvin);
 */
            light->on_off           = msg->payload.lx_protocol_light_state.power;
            break;
        }
        
    }
}

void extern setPower(lx_light_t *light, bool on_off, int delay) {
    int recvlen;
    lx_protocol_t header;
    header.protocol = 1024;
    header.addressable = 1;
    header.tagged = 1;
    header.origin = 0;
    header.source = 1;
    for (int i = 0; i < 8; i++)
        header.target[i] = 0;
    header.ack_required = 0;
    header.res_required = 0;
    header.sequence = 0;
    header.reserved64 = 0;
    for(int i = 0; i < 6; i++) {
        header.reserved[i] = 0;
    }
    header.type = LX_PROTOCOL_LIGHT_SET_POWER;
    header.payload.lx_protocol_light_set_power.level = on_off ? 0xFFFF : 0;
    header.payload.lx_protocol_light_set_power.duration = delay;
    header.size = lx_protocol_sizeof(lx_protocol_light_set_power_t);
    udpSendMsg(&unicast_udp_socket, header, light->addr);
}

void extern setColor(lx_light_t *light, float* color, int delay) {
    int recvlen;
    lx_protocol_t header;
    header.protocol = 1024;
    header.addressable = 1;
    header.tagged = 1;
    header.origin = 0;
    header.source = 1;
    for (int i = 0; i < 8; i++)
        header.target[i] = 0;
    header.ack_required = 0;
    header.res_required = 0;
    header.sequence = 0;
    header.reserved64 = 0;
    for(int i = 0; i < 6; i++) {
        header.reserved[i] = 0;
    }
    header.type = LX_PROTOCOL_LIGHT_SET_COLOR;
    header.payload.lx_protocol_light_set_color.color.hue = color[0]/360*0xFFFF;
    header.payload.lx_protocol_light_set_color.color.saturation = color[1]*0xFFFF;
    header.payload.lx_protocol_light_set_color.color.brightness = color[2]*0xFFFF;
    header.payload.lx_protocol_light_set_color.color.kelvin = color[3];
    header.payload.lx_protocol_light_set_color.duration = delay;
    
    header.size = lx_protocol_sizeof(lx_protocol_light_set_color_t);
    udpSendMsg(&unicast_udp_socket, header, light->addr);
}