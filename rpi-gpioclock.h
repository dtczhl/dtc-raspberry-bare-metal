/*
    Reference:
	The I2S sound thread. www.raspberrypi.org/forums/viewtopic?t=8496&f=44
	Accessing the hardware pwm peripheral on the raspberry pi in c++.
	www.hertaville.com/rpipwm.html


    Huanle Zhang at UC Davis. www.huanlezhang.com
    Last Update: May 27, 2017

*/

#ifndef _RPI_GPIO_CLOCK_H_
#define _RPI_GPIO_CLOCK_H_

#include "dtcArgs.h"

#define GPIO_CLOCK_PWM_OFFSET	(40 * 4)

#define GPIO_CLOCK_PWD	(0x5A << 24)

#define CM_CTL_MASH_1	( 1 << 9 )
#define CM_CTL_BUSY	( 1 << 7 )
#define CM_CTL_KILL	( 1 << 5 )
#define CM_CTL_ENAB	( 1 << 4 )
#define CM_CTL_SRC_OSCI	( 1 << 0 )

#define CM_DIV_DIVI_SHIFT   12
#define CM_DIV_DIVF_SHIFT   0

typedef struct {
    volatile unsigned int ctl;
    volatile unsigned int div;
} Clock_manager;

void setGPIOClock(int divi, int divf);

#endif
