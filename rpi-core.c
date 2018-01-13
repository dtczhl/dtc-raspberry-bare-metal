/*
    Reference:
	Trying Bare Metal on Raspberry Pi 2. www.raspberrypi.org/forums/viewtopic.php?p=701773


    Huanle Zhang at UC Davis. www.huanlezhang.com
    Last Update: May 16, 2017

*/

#include "rpi-core.h"
#include "rpi-gpio.h"
#include "rpi-i2s.h"
#include "rpi-pwm.h"
#include "rpi-serial.h"
#include "rpi-networking.h"
#include "dtcMediaPlayer.h"

volatile int pCoreRun[4] = {0, 0, 0, 0};

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
    
    // for networking
    // startNetworking();
	
	setGPIOMode(26, OUTPUT);
    while(1){
		setGPIOPin(26, HIGH);
		waitMicroSeconds(1000000);
		setGPIOPin(26, LOW);
		waitMicroSeconds(1000000);
	}
}

void core_2_main(void){

    // startMediaPlayer();
    while(1);
}


void core_3_main(void){

    // startPwmAudio();
    while (1);    
}

