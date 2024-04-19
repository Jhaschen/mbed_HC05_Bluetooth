/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include <cstdio>
BufferedSerial pc(USBTX, USBRX,9600);
BufferedSerial bt(D1, D0,9600);




int main()
{
    // Initialise the digital pin LED1 as an output
    DigitalOut led1(LED1);
    DigitalOut led2(LED2);
    led1 =1;
    led2= 1;

    char buffer[100];
    sprintf(buffer, "Bluetooth HC-05 Test\n\t");
    bt.write(buffer,22);
    sprintf(buffer, "LED 1 ='1', LED 2 = '2' LEDs aus = '0'\n\r");
    bt.write(buffer,40);
    while (true) {

        if(bt.readable()){

            bt.read(buffer,10);
            if(buffer[0]=='1'){
                led1=0;
             
            }else if (buffer[0]=='2') {
           
            led2= 0;
            }else if (buffer[0]=='0') {
            led1 =1;
            led2= 1;
            }
           pc.write(buffer,10) ;
        }
        
        ThisThread::sleep_for(100ms);
    }
}