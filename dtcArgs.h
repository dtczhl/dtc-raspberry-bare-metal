/*

    Huanle Zhang at UC Davis. www.huanlezhang.com
    Last Update: April 28, 2017

*/

#ifndef _DTC_ARGS_H_
#define _DTC_ARGS_H_

#define BCM2837_BASE	0x3F000000UL

#define GPIO_BASE	( BCM2837_BASE + 0x200000 )

#define TIMER_BASE	( BCM2837_BASE + 0xB000 )

#define INTERRUPT_BASE	TIMER_BASE

#define SYSTIMER_BASE	( BCM2837_BASE + 0x3000 )

#define I2S_BASE	( BCM2837_BASE + 0x203000 )

#define GPIO_CLOCK_BASE	( BCM2837_BASE + 0x101000 )

#define PWM_BASE	( BCM2837_BASE + 0x20C000 )

// #define GPIO_CLOCK_BASE	( PWM_BASE + 40 )

#endif
