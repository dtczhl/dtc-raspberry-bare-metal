/*
    
    Reference:
	Accessing the hardware pwm peripheral on the raspberry pi in c++.
	www.hertaville.com/rpipwm.html


    Huanle Zhang at UC Davis
	www.huanlezhang.com

*/

#ifndef _RPI_PWM_H_
#define _RPI_PWM_H_

#define PWM_CTL_SBIT1	( 1 << 3 )
#define PWM_CTL_PWEN1	( 1 << 0 )

#define PWM_STA_STA1	( 1 << 9 )
#define PWM_STA_BERR	( 1 << 8 )
#define PWM_STA_GAPO1	( 1 << 4 )

#define PWM_BUFFER_SIZE	2048	

typedef struct {

    volatile unsigned int ctl;	    // 0x00
    volatile unsigned int sta;	    // 0x04
    volatile unsigned int dmac;	    // 0x08
    volatile unsigned int unused1;  // 0x0c
    volatile unsigned int rng1;	    // 0x10
    volatile unsigned int dat1;	    // 0x14
    volatile unsigned int fif1;	    // 0x18
    volatile unsigned int unused2;  // 0x1c
    volatile unsigned int rng2;	    // 0x20
    volatile unsigned int dat2;	    // 0x24
} Pwm_registers;

void startPwmAudio(void);

void pwmInitBuffer(char*);
void pwmAddBuffer(void);
inline int pwmInitialized(void);
inline void pwmStop(void);
inline void pwmResume(void);
inline void pwmSetVol(double volRatio);

#endif
