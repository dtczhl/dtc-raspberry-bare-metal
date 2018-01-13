/*
    Reference: 
	Brian Sidebotham's Bare Metal Pi Tutorial. www.valvers.com
	Davis Welch's Pi Repo. www.github.com/dwelch67/raspberrypi
    
    
    Huanle Zhang at UC Davis. www.huanlezhang.com 
    April 14, 2017

*/

#include "rpi-systimer.h"


Systimer_t* systemTimer = (Systimer_t *)SYSTIMER_BASE;

void waitMicroSeconds( unsigned long long us )
{
    unsigned int us_hi = (unsigned int)(us >> 32);
    unsigned int us_lo = (unsigned int)(us);
    // current time
    unsigned int ct_hi = systemTimer->counter_hi;
    unsigned int ct_lo = systemTimer->counter_lo;
    
    while ((systemTimer->counter_hi - ct_hi) < us_hi)
	;
    while ((systemTimer->counter_lo - ct_lo) < us_lo)
	;

}
