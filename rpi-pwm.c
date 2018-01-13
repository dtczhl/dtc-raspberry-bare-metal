/*

    Reference:
	Accessing the hardware pwm peripheral on the raspberry pi in c++.
	www.hertaville.com/rpipwm.html


    Huanle Zhang at UC Davis. www.huanlezhang.com
    Last Update: May 27, 2017

*/

#include "rpi-gpioclock.h"
#include "rpi-pwm.h"
#include "rpi-gpio.h"

volatile Pwm_registers* sysPwm = (Pwm_registers *) PWM_BASE;

volatile static char* pData;
volatile static int status = -1; // -1 - not start; 0 - start; 1 - stop
volatile static double volScale = 1.0;


volatile static int bWritable = 0; // 0-playing, 1-waiting, 2-ready

void pwmInitBuffer(char *data){
    pData = data;
}

void pwmAddBuffer(void){
    bWritable = 2;
}

inline int pwmBufferWritable(void){
    if (bWritable == 1) return 1;
    else return 0;
}

inline int pwmInitialized(void){
   return status; 
}

inline void pwmStop(void){
    status = 1;
}

inline void pwmResume(void){
    status = 0;    
}

inline void pwmSetVol(double volRatio){
    volScale = volRatio;    
}

void startPwmAudio(){

    char data = 0;
    int i = 0;
    
    setGPIOAlt(12, 0);
   
    setGPIOClock(2, 0); // maximum frequency 37.5K, 256 resolution

    sysPwm->ctl = 0;
    sysPwm->rng1 = 256;
    sysPwm->dat1 = 128;
    sysPwm->ctl |= PWM_CTL_PWEN1;
    
    status = 1;
    
    bWritable = 1;

    while (1){

	if(status == 1){ // stop
	    waitMicroSeconds(10);
	    continue;    
	}

	if (bWritable == 1) {
	    waitMicroSeconds(10);
	    continue;
	}

	bWritable = 0;
	for (i = 0; i < PWM_BUFFER_SIZE; i++){
	    sysPwm->dat1 = pData[i];
	    waitMicroSeconds(27);
	}
	bWritable = 1;

    }
}

