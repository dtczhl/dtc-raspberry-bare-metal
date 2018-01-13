/*
    Reference: 
	Brian Sidebotham's Bare Metal Pi Tutorial. www.valvers.com
	Davis Welch's Pi Repo. www.github.com/dwelch67/raspberrypi
    
    
    Huanle Zhang at UC Davis. www.huanlezhang.com 
    April 28, 2017

*/

#include "rpi-armtimer.h"

volatile Arm_timer_t* sysArmTimer = (Arm_timer_t*) ARMTIMER_BASE;

void setTimer(unsigned int us)
{
  // note: UINT: 4294 s
  sysArmTimer->Load = us - 1;
  sysArmTimer->IRQ_ClearAck = 1;
  sysArmTimer->Control = ARMTIMER_CONTROL_23BIT | ARMTIMER_CONTROL_PRESCALE_1
  | ARMTIMER_CONTROL_TIMER_INTERRUPT_ENABLE | ARMTIMER_CONTROL_TIMER_ENABLE;
}

void cancelTimer(void)
{
    sysArmTimer->Control = ARMTIMER_CONTROL_TIMER_INTERRUPT_DISABLE |
    ARMTIMER_CONTROL_TIMER_DISABLE;
}

inline void clearTimerPendingBit(void)
{
    sysArmTimer->IRQ_ClearAck = 1;    
}
