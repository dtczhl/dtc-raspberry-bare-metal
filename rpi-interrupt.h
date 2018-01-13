/*
    Reference: 
	Brian Sidebotham's Bare Metal Pi Tutorial. www.valvers.com
	Davis Welch's Pi Repo. www.github.com/dwelch67/raspberrypi
    
    
    Huanle Zhang at UC Davis. www.huanlezhang.com 
    Last Update: April 28, 2017

*/

#ifndef _RPI_INTERRUPT_H_
#define _RPI_INTERRUPT_H_

#define INTERRUPT_CONTROLLER_BASE ( INTERRUPT_BASE + 0x200 )

// ARM periherals interrupt table
#define INTERRUPT_TABLE_ARM_TIMER		( 1 << 0 )
#define INTERRUPT_TABLE_ARM_MAILBOX		( 1 << 1 )
#define INTERRUPT_TABLE_ARM_DOORBELL_0		( 1 << 2 )
#define INTERRUPT_TABLE_ARM_DOORBELL_1		( 1 << 3 )
#define INTERRUPT_TABLE_GPU0_HALTED		( 1 << 4 )
#define INTERRUPT_TABLE_GPU1_HALTED		( 1 << 5 )
#define INTERRUPT_TABLE_ILLEGAL_ACCESS_TYPE_1	( 1 << 6 )
#define INTERRUPT_TABLE_ILLEGAL_ACCESS_TYPE_0	( 1 << 7 )

#define INTERRUPT_BASIC_PENDING_TIMER	( 1 << 0 )

typedef struct {
    volatile unsigned int basic_pending;
    volatile unsigned int GPU_pending_1;
    volatile unsigned int GPU_pending_2;
    volatile unsigned int FIQ;
    volatile unsigned int interrupt_enable_1;
    volatile unsigned int interrupt_enable_2;
    volatile unsigned int base_interrupt_enable;
    volatile unsigned int interrupt_disable_1;
    volatile unsigned int interrupt_disable_2;
    volatile unsigned int base_disable;
} Interrupt_registers;

void startTimerTask(unsigned int us, void (*f)(void));

#endif
