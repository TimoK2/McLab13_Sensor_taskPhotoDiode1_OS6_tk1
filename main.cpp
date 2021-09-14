/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
************************************************************************
*
* Test of the Pmod ambient light sensor, code for task 1
*
*************************************************************************
* Description: McLab13_Sensor_SPI_PmodALS_OS6_task1
* The ambient light value will be read and converted to LUX. 
*
* Material
* 1. ST NUCLEO L432KC , NXP FRDM-K64F  
* or some other micro controller board 
*
* 2. Option for task1: Photo Diode BPW34, OpAmp TLC721, 330k, 12 pF
*    Detailed circuit diagram in the instruction sheet. 
* 
* 
* Timo Karppinen 25.11.2020
**************************************************************/
#include "mbed.h"

DigitalOut LED(D2);  // A pin for connecting a LED

AnalogIn ainPD(A0);  // A pin to interface OpAmp output 0V to 3,3V 

int alScaled = 0;   // The voltage converted to illuminance Lux value

unsigned short pd12bit = 0; // 16 bit variable to store the conversion result
            // from the internal analog to digital converter
            // in the L432KC the ADC resolution is 12 bit. 

float pdScaledF = 0.0;      // for the value calculated for the correct scale

int main()
{   

    while (true) {
   
        pd12bit = ainPD.read_u16() >>4;  // leftmost 12 bits moved 4 bits to right.
        printf("Ambient light PD sensor 12 bit 0...4095 =  '%d' \r\n", pd12bit);
        pdScaledF = (float(pd12bit))*(float(0.1));// write the correct scaling multiplier      
        if (pdScaledF > 100){ 
            LED.write(0);
            printf("Light OK for working. \n\n");
            }
        else{
            LED.write(1);
            printf("Too low light for working. \n\n");
            }
            
        ThisThread::sleep_for(3000ms);
    }
}

