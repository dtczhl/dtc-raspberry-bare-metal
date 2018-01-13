/*
    Reference:
	The I2S sound thread. www.raspberrypi.org/viewtopic.php?t=8496&f=44
	Accessing the hardware PWM Peripheral on the Raspberry Pi in C++.
	www.hertaville.com/rpipwm.html

    
    Huanle Zhang at UC Davis. www.huanlezhang.com
    Last Update: May 28, 2017

*/


#include "rpi-gpioclock.h"


volatile Clock_manager* sysClockManager = (Clock_manager *) (GPIO_CLOCK_BASE + GPIO_CLOCK_PWM_OFFSET);

void setGPIOClock(int divi, int divf)
{

    sysClockManager->ctl = GPIO_CLOCK_PWD | CM_CTL_KILL;

    while ( sysClockManager->ctl & CM_CTL_BUSY)
	;

    sysClockManager->div = GPIO_CLOCK_PWD | (divi << CM_DIV_DIVI_SHIFT) | (divf << CM_DIV_DIVF_SHIFT);

    sysClockManager->ctl = GPIO_CLOCK_PWD | CM_CTL_MASH_1 | CM_CTL_SRC_OSCI | CM_CTL_ENAB;

    return;
}

