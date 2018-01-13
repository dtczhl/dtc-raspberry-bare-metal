/*
    Reference: 
	Brian Sidebotham's Bare Metal Pi Tutorial. www.valvers.com
	Davis Welch's Pi Repo. www.github.com/dwelch67/raspberrypi
    
    
    Huanle Zhang at UC Davis. www.huanlezhang.com 
    Last Update: May 25, 2017

*/

#include <string.h>
#include <stdlib.h>

#include "rpi-gpio.h"
#include "rpi-systimer.h"
#include "rpi-interrupt.h"
#include "rpi-armtimer.h"
#include "rpi-core.h"
#include "rpi-i2s.h"

extern volatile int pCoreRun[];

void core0_main(void);
void timerTaskFunc(void);

void kernel_main( unsigned int r0, unsigned int r1, unsigned int atags )
{

    _disable_interrupts();
    
    // 

    _enable_interrupts();
    


    startTimerTask(1000000, timerTaskFunc);

    // start_core_1();
    // start_core_2();
    // start_core_3();

    core0_main();
}

void timerTaskFunc(void)
{
    static int lit = 0;
    if (lit){
	lit = 0;
	setGPIO(5, HIGH);
    } else {
	lit = 1;
	setGPIO(5, LOW);
    }
}

void core0_main(void)
{
    volatile int i = 0;
    while (1){
	i++;	
    }
 
}
