//
//  lifx-udp.h
//  lifx-sdk-lib
//
//  Created by Apple on 6/30/15.
//  Copyright (c) 2015 LIFX. All rights reserved.
//

#ifndef lifx_sdk_lib_lifx_udp_h
#define lifx_sdk_lib_lifx_udp_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>


typedef struct {
    int socket;
    void* buffer;
} UDPSocket;

#endif
