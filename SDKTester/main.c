//
//  main.c
//  SDKTester
//
//  Created by Apple on 6/30/15.
//  Copyright (c) 2015 LIFX. All rights reserved.
//

#include <stdio.h>
#include "lifx-sdk.h"
#include <string.h>
#include <assert.h>


void printMac(uint8_t mac_addresses[MAX_NUMBER_MAC_ADDRESSES][8], int size) {
    for (int i = 0; i < size; i++) {
        printf("#%02d %X::%X::%X::%X::%X::%X::%X::%X\n",i + 1, mac_addresses[i][0],mac_addresses[i][1],mac_addresses[i][2],mac_addresses[i][3],mac_addresses[i][4],mac_addresses[i][5],mac_addresses[i][6],mac_addresses[i][7]);
    }
}
void copyMac(uint8_t mac_addresses[MAX_NUMBER_MAC_ADDRESSES][8], uint8_t target[8], int index) {
    for (int i = 0; i < 8; i++) {
        target[i] = mac_addresses[index][i];
    }
}
int main(int argc, const char * argv[])
{
    uint8_t **mac_addresses = NULL;
    char* input;
    while(1) {
        int index;
        size_t len = 0;
        printf("Enter a Command\n");
        getline(&input, &len, stdin);
        if (strcmp(input, "init\n") == 0) {
            lx_light_init();
            mac_addresses = lx_light_get_macs();
            int size = lx_light_get_size();
            printf("size is %d\n", size);
            printMac(mac_addresses, size);
            printf("Initializing\n");
        }
        else if (strcmp(input, "getMacs\n") == 0) {
            //mac_addresses = lx_light_get_macs();
            int size = lx_light_get_size();
            printMac(mac_addresses, size);
        }
        else if (strcmp(input, "getName\n") == 0) {
            uint8_t target[8];
            printf("Input Light Bulb Number\n");
            scanf("%d", &index);
            copyMac(mac_addresses, target, index);
            char *name= lx_light_get_name(target);
            printf("name = %s\n", name);
        }
        else if (strcmp(input, "getPower\n") == 0) {
            uint8_t target[8];
            printf("Input Light Bulb Number\n");
            scanf("%d", &index);
            copyMac(mac_addresses, target, index);
            if (lx_light_get_on_off(target))
                printf("it's on\n");
            else
                printf("it's off\n");
        }
        else if (strcmp(input, "getColor\n") == 0) {
            uint8_t target[8];
            printf("Input Light Bulb Number\n");
            scanf("%d", &index);
            copyMac(mac_addresses, target, index);
            float *color = lx_light_get_color(target);
            printf("HSBK = (%f, %f, %f, %f)\n", *(color), *(color +1), *(color + 2), *(color + 3));
        }
        else if (strcmp(input, "setColor\n") == 0) {
            uint8_t target[8];
            printf("Input Light Bulb Number\n");
            scanf("%d", &index);
            copyMac(mac_addresses, target, index);
            float colors[4];
            printf("Input Hue\n");
            scanf("%f", &colors[0]);
            printf("Input Saturation\n");
            scanf("%f", &colors[1]);
            printf("Input Brightness\n");
            scanf("%f", &colors[2]);
            printf("Input Kelvin\n");
            scanf("%d", &index);
            colors[3] = (float) index;
            for (int i = 0; i < 4; i++) {
                printf("%f ", colors[i]);
            }
            printf("\n");
            printf("Input Delay\n");
            scanf("%d", &index);
            lx_light_set_color(target, colors, index);
        }
        
        else if (strcmp(input, "setPower\n") == 0) {
            uint8_t target[8];
            printf("Input Light Bulb Number\n");
            scanf("%d", &index);
            copyMac(mac_addresses, target, index);
            bool on_off;
            printf("Input On Or Off\n");
            scanf("%d", &index);
            if (index) {
                on_off = true;
            }
            else {
                on_off = false;
            }
            printf("Input Delay\n");
            scanf("%d", &index);
            lx_light_set_on_off(target, on_off, index);
        }

        else if (strcmp(input, "update\n") == 0) {
            lx_light_get_active();
            printf("UPDATING\n");
            int size = lx_light_get_size();
            mac_addresses = lx_light_get_macs();
            printMac(mac_addresses, size);
            printf("Size is %d\n", size);
        }
        
        else if (strcmp(input, "destroy\n") == 0) {
            lx_light_destroy();
            //return 0;
        }
    }
}



