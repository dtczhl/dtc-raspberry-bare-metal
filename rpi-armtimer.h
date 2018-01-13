/*
    Reference: 
	Brian Sidebotham's Bare Metal Pi Tutorial. www.valvers.com
	Davis Welch's Pi Repo. www.github.com/dwelch67/raspberrypi
    
    
    Huanle Zhang at UC Davis. www.huanlezhang.com 
    April 28, 2017

*/

#ifndef _RPI_ARM_TIMER_H_
#define _RPI_ARM_TIMER_H_

#include "dtcArgs.h"

#define ARMTIMER_BASE ( TIMER_BASE + 0x400 )

#define ARMTIMER_CONTROL_16BIT	( 0 << 1 )
#define ARMTIMER_CONTROL_23BIT	( 1 << 1)

#define ARMTIMER_CONTROL_PRESCALE_1	( 0 << 2 )
#define ARMTIMER_CONTROL_PRESCALE_16	( 1 << 2 )
#define ARMTIMER_CONTROL_PRESCALE_256	( 2 << 2 )

#define ARMTIMER_CONTROL_TIMER_INTERRUPT_DISABLE    ( 0 << 5 )
#define ARMTIMER_CONTROL_TIMER_INTERRUPT_ENABLE	    ( 1 << 5 )

#define ARMTIMER_CONTROL_TIMER_DISABLE	( 0 << 7 )
#define ARMTIMER_CONTROL_TIMER_ENABLE	( 1 << 7 )

typedef struct {
    volatile unsigned int Load;
    volatile unsigned int Value;
    volatile unsigned int Control;
    volatile unsigned int IRQ_ClearAck;
    volatile unsigned int RAW_IRQ;
    volatile unsigned int Masked_IRQ;
    volatile unsigned int Reload;
    volatile unsigned int PreDivider;
    volatile unsigned int Free_Running_Counter;
} Arm_timer_t;

void setTimer(unsigned int us);
void cancelTimer(void);
inline void clearTimerPendingBit(void);

#endif
