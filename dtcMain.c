/*
    Reference: 
	Brian Sidebotham's Bare Metal Pi Tutorial. www.valvers.com
	Davis Welch's Pi Repo. www.github.com/dwelch67/raspberrypi
    
    
    Huanle Zhang at UC Davis 
	www.huanlezhang.com 

*/

#include <string.h>
#include <stdlib.h>

#include "rpi-gpio.h"
#include "rpi-systimer.h"
#include "rpi-interrupt.h"
#include "rpi-armtimer.h"
#include "rpi-core.h"
#include "dtcLed.h"

// defined in dtcLed.c
extern volatile int dtcLedCtrl_1;

void core0_main(void);
void timerTaskFunc(void);

void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{

	// to enable timer interruption 
    _disable_interrupts();
    _enable_interrupts();
    
	// demo: init LEDs
	initLeds(); 

	// 1st argument: time interval in microsecond to trigger an interrupt
	// 2nd argument: callback function when interrupted
	//					timerTaskFunc is defined below
    startTimerTask(1000000, timerTaskFunc);

	// Raspi 2/3 has four cores. Enable other three cores in addition to current Core 0
	// start_core_* is defined in rpi-core.c
    start_core_1();
    start_core_2();
    start_core_3();

	// Core 0 continues to do its own work
	// core0_main defined below
    core0_main();
}

void timerTaskFunc(void)
{
    // interruption routine
	dtcLedCtrl_1 = 1 - dtcLedCtrl_1;
}

void core0_main(void)
{
    
    while (1){
		;	
    }
 
}
