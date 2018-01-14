/*
    Reference:
	Trying Bare Metal on Raspberry Pi 2. www.raspberrypi.org/forums/viewtopic.php?p=701773


    Huanle Zhang at UC Davis
	www.huanlezhang.com

*/

#include "rpi-core.h"
#include "rpi-gpio.h"
#include "rpi-pwm.h"
#include "dtcLed.h"

extern volatile int dtcLedCtrl_1; // defined in dtcLed.c

volatile static int ledStatus_R = 0;
volatile static int ledStatus_G = 0;
volatile static int ledStatus_B = 0;

volatile unsigned int* pCore;

void start_core_1(void){
    pCore = (unsigned int*) CORE1_START_ADDRESS;
    *pCore = (unsigned int) &_core_1_main;
}

void start_core_2(void){
    pCore = (unsigned int*) CORE2_START_ADDRESS;
    *pCore = (unsigned int) &_core_2_main;
}

void start_core_3(void){
    pCore = (unsigned int*) CORE3_START_ADDRESS;
    *pCore = (unsigned int) &_core_3_main;
    
}

void core_1_main(void){

	// control R
	while(1){
		if (ledStatus_R !=  dtcLedCtrl_1){
			setGPIOPin(DTC_R_PIN, dtcLedCtrl_1);
			ledStatus_R = dtcLedCtrl_1;
		}
	}
}

void core_2_main(void){

    // control G
    while(1){
		if (ledStatus_G !=  dtcLedCtrl_1){
			setGPIOPin(DTC_G_PIN, dtcLedCtrl_1);
			ledStatus_G = dtcLedCtrl_1;
		}
	}

}


void core_3_main(void){

    // control B
    while(1){
		if (ledStatus_B !=  dtcLedCtrl_1){
			setGPIOPin(DTC_B_PIN, dtcLedCtrl_1);
			ledStatus_B = dtcLedCtrl_1;
		}
	}
     
}

