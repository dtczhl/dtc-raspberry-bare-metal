/*
    Reference: 
	Brian Sidebotham's Bare Metal Pi Tutorial. www.valvers.com
	Davis Welch's Pi Repo. www.github.com/dwelch67/raspberrypi
    
    
    Huanle Zhang at UC Davis. www.huanlezhang.com 
    Last Update: April 28, 2017

*/

#include "rpi-interrupt.h"
#include "rpi-gpio.h"
#include "rpi-armtimer.h"

typedef void (*TimerTask)(void);
static TimerTask myTimerTask;

volatile Interrupt_registers* sysInterrupt = (Interrupt_registers *)
INTERRUPT_CONTROLLER_BASE;

void startTimerTask(unsigned int us, void (*f)(void))
{
    sysInterrupt->base_disable = INTERRUPT_TABLE_ARM_TIMER;
    myTimerTask = f;
    setTimer(us);
    sysInterrupt->base_interrupt_enable = INTERRUPT_TABLE_ARM_TIMER;
}

void c_undefined_handler(void)
{
    // do nothing    
}

void c_swi_handler(void){
    
}

void c_prefetch_handler(void){
    
}

void c_data_handler(void){
    
}

void c_hyp_handler(void){
    
}

void c_irq_handler(void){
    
    _disable_interrupts();
    
    if ( ((sysInterrupt->basic_pending) & INTERRUPT_BASIC_PENDING_TIMER) == 1){
	// timer task irq
	clearTimerPendingBit();
	myTimerTask();
    }

    _enable_interrupts();

}

void c_fiq_handler(void){
    
}
