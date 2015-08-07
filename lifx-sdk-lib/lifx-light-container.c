//
//  lifx-light-container.c
//  lifx-sdk-lib
//
//  Created by Apple on 6/30/15.
//  Copyright (c) 2015 LIFX. All rights reserved.
//

#include <stdio.h>
#include "lifx-light-container.h"
#include "protocol.h"

#define PORT 56700

extern void udpSendMsg(UDPSocket *udp, lx_protocol_t header, struct sockaddr_in sndAddr);

extern void udpRecvMsg(UDPSocket *udp);

extern void initUDP(UDPSocket *udp, int broadcast);

extern void destroyUDP(UDPSocket *udp);

void discover(lx_light_container_t* lightCollection);

void getInfo(lx_light_container_t *lightCollection);

UDPSocket broadcast_udp_socket;

UDPSocket unicast_udp_socket;

void print (lx_light_t *light) {
    printf("Mac: %X::%X::%X::%X::%X::%X\n", light->target[0], light->target[1], light->target[2], light->target[3], light->target[4], light->target[5]);
}
void removeDuplicates(lx_light_container_t *lightCollection) {
    if (lightCollection == NULL) {
        return;
    }
    printf("Removing Duplicates\n");
    int counter = 0;
    lx_light_t *temp = lightCollection->start;
    lx_light_t *next;
    lx_light_t *duplicate;
    while(temp != NULL && temp->next != NULL) {
        next = temp;
        while (next->next != NULL) {
            duplicate = next->next;
            if (temp->addr.sin_addr.s_addr == duplicate->addr.sin_addr.s_addr) {
                next->next = duplicate->next;
                free(duplicate);
                counter++;
            }
            else
                next = next->next;
        }
        temp = temp->next;
    }
    printf("Removed %d duplicates\n", counter);
}

void extern init(lx_light_container_t *lightCollection) {
    initUDP(&broadcast_udp_socket, 1);
    initUDP(&unicast_udp_socket, 0);
    discover(lightCollection);
    getInfo(lightCollection);
}

void getInfo(lx_light_container_t *lightCollection){
    lx_light_t *temp = lightCollection->start;
    int counter = 0;
    while(temp != NULL) {
        //printf("%s %d\n", inet_ntoa(light->addr.sin_addr), light->socket);
        getName(temp);
        for (int i = 0; i < 8; i++)
            lightCollection->mac_addresses[counter][i] = temp->target[i];
        counter++;
        temp = temp->next;
        
    }
    lightCollection->size = counter;
    //printf("Counter = %d\n", counter);
}
void destroyLinkedList(lx_light_container_t *lightCollection) {
    lx_light_t *temp = lightCollection->start;
    lightCollection->start = lightCollection->start->next;
    printf("Destroying List\n");
    int counter = 0;
    while(lightCollection->start != NULL) {
        print(temp);
        free(temp);
        counter++;
        temp = lightCollection->start;
        lightCollection->start = lightCollection->start->next;
    }
    counter++;
    print(temp);
    free(temp);
    printf("REMOVED %d nodes\n", counter);
}
void extern deinit(lx_light_container_t *lightCollection) {
    destroyLinkedList(lightCollection);
}

void broadcast(lx_light_container_t* lightCollection) {
    struct sockaddr_in sndaddr;
    memset((char *) &sndaddr, 0, sizeof(struct sockaddr_in));
    sndaddr.sin_family = AF_INET;
    sndaddr.sin_port = htons(PORT);
    sndaddr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    
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
    header.reserved16 = 0;
    for(int i = 0; i < 6; i++) {
        header.reserved[i] = 0;
    }
    header.type = LX_PROTOCOL_DEVICE_GET_SERVICE;
    header.size = offsetof(lx_protocol_t,payload);
    
    struct sockaddr_in recvaddr;
    socklen_t addrlen = sizeof(recvaddr);
    int recvlen;
    int counter = 0;
    
    lx_protocol_t msg;
    lx_light_t *next;
    lx_light_t *temp;
    next = lightCollection->start;
    while ((counter) == 0) {
        udpSendMsg(&broadcast_udp_socket, header, sndaddr);
        while (1) {
            recvlen = recvfrom(broadcast_udp_socket.socket, &msg, sizeof(lx_protocol_t), 0, (struct sockaddr *)&recvaddr, &addrlen);
            if (recvlen > 0) {
                if (msg.type == LX_PROTOCOL_DEVICE_STATE_SERVICE) {
                    counter++;
                    next = (lx_light_t *)malloc(sizeof(lx_light_t));
                    for (int i = 0; i < 8; i++)
                        next->target[i] = msg.target[i];
                    next->addr = recvaddr;
                    next->next = NULL;
                    if (lightCollection->start == NULL) {
                        lightCollection->start = next;
                    }
                    else {
                        temp->next = next;
                    }
                    temp = next;
                }
            }
        
            if (recvlen == -1) {
                printf("Discovery done found %d bulbs \n", counter);
                break;
            }
        }
    }
}

void extern getActive(lx_light_container_t* lightCollection) {
    destroyLinkedList(lightCollection);
    discover(lightCollection);
    getInfo(lightCollection);
}
void discover(lx_light_container_t* lightCollection) {
    broadcast(lightCollection);
    removeDuplicates(lightCollection);
    return;
}
