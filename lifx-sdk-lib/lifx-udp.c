//
//  lifx-udp.c
//  lifx-sdk-lib
//
//  Created by Apple on 6/30/15.
//  Copyright (c) 2015 LIFX. All rights reserved.
//

#include "lifx-udp.h"
#include "protocol.h"

extern void initUDP(UDPSocket *udp, int broadcast) {
    if ((udp->socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        fprintf(stderr, "Failure to create socket");
        return;
    }
    udp->buffer = malloc(sizeof(lx_protocol_t));
    struct sockaddr_in srcaddr;
    memset((char *)&srcaddr, 0, sizeof(srcaddr));
	srcaddr.sin_family = AF_INET;
	srcaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	srcaddr.sin_port = 0;;
    
    if (bind(udp->socket, (struct sockaddr *) &srcaddr, sizeof(srcaddr)) < 0) {
		perror("broadcast bind failed");
		return;
	}
    
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 200000;
    if (setsockopt (udp->socket, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
                    sizeof(timeout)) < 0)
        perror("setsockopt failed\n");
    if (broadcast) {
        int broadcastEnable=1;
        setsockopt(udp->socket, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
    }
}

extern void udpSendMsg(UDPSocket *udp, lx_protocol_t header, struct sockaddr_in sndAddr) {
    if (sendto(udp->socket, &header, header.size, 0, (struct sockaddr *) &sndAddr, sizeof(sndAddr)) == -1)
        perror("error");
}

extern void udpRecvMsg(UDPSocket *udp) {
    struct sockaddr_in recvAddr;
    long recvLen;
    lx_protocol_t msg;
    socklen_t addrLen = sizeof(recvAddr);
    while (1) {
        recvLen = recvfrom(udp->socket, &msg, sizeof(lx_protocol_t), 0, (struct sockaddr *) &recvAddr, &addrLen);
        if (recvLen > 0) {
            memcpy(udp->buffer, &msg, sizeof(msg));
        }
        else if (recvLen == -1)
            break;
    }
}
