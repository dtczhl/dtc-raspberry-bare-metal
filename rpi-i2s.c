/*

    under testing ... 

*/



#include <limits.h>
#include <math.h>
#include "rpi-i2s.h"
#include "rpi-gpio.h"
#include "rpi-gpioclock.h"

void play();

volatile PCM_registers* sysPcm = (PCM_registers *)  I2S_BASE;

const int FS = 48000;
int mOutFreq = 440;

void startAudio(){

    // 48 Hz
    volatile int i;

    setGPIOAlt(4, 0);

    setGPIOClock(12, 512); 
  
    setGPIOAlt(18, 0);
    setGPIOAlt(19, 0);
    setGPIOAlt(20, 0);
    setGPIOAlt(21, 0);

    sysPcm->cs &= ~(1<<24);
    waitMicroSeconds(100);
    sysPcm->cs = 0;
    waitMicroSeconds(100);
    sysPcm->cs |= 1 << 3 | 1 << 4 | 1 << 5;
    waitMicroSeconds(10);
    sysPcm->txc = 1 << 31 | 1 << 30 | 8 << 16;
    sysPcm->mode =  31 << 10;
    sysPcm->cs |= 1 << 25;
    waitMicroSeconds(50);
    sysPcm->cs |= 0x01;
    sysPcm->cs |= 0x02;

    sysPcm->cs |= 1 << 24;
    
    while ((sysPcm->cs & (1<<19)) == 0)
	;

    setGPIO(5,HIGH);

    while (1){
	while (sysPcm->cs & 1 << 19){
	    sysPcm->fifo = 0xA0A0A0A0;    
	}	
    }

   /*
    setGPIOAlt(PCM_CLK, PCM_CLK_GPIO_ALT);
    setGPIOAlt(PCM_FS, PCM_FS_GPIO_ALT);
    setGPIOAlt(PCM_DIN, PCM_DIN_GPIO_ALT);
    setGPIOAlt(PCM_DOUT, PCM_DOUT_GPIO_ALT);
*/
    // frame length, frame sync length, 32bit
   
    sysPcm->cs &= ~(PCM_CS_SYNC);
    for (i = 500000; i > 0; i--);
    
    sysPcm->cs = 0;
    for (i = 500000; i > 0; i--)
	;

    sysPcm->cs = PCM_CS_RXCLR | PCM_CS_TXCLR | PCM_CS_TXTHR_F;
    for (i = 500000; i > 0; i--)
	;

    sysPcm->txc = PCM_TXC_CH1WEX | PCM_TXC_CH1EN | (8 << PCM_TXC_CH1WID_BIT);
    sysPcm->mode = (31 << PCM_MOD_FLEN_BIT);

    sysPcm->cs |= PCM_CS_STBY;

    for (i = 500000; i > 0; i--)
	;

    sysPcm->cs |= PCM_CS_EN;
    sysPcm->cs |= PCM_CS_TXON;

    for (i = 500000; i > 0; i--)
	;

    setGPIO(5, HIGH);
    play();
    
    sysPcm->mode = (31 << PCM_MOD_FLEN_BIT) | (31 << PCM_MOD_FSLEN_BIT);
    sysPcm->txc = PCM_TXC_CH1WEX | PCM_TXC_CH1EN | (0xF << PCM_TXC_CH1WID_BIT);
    sysPcm->fifo = UINT_MAX;
    sysPcm->cs = PCM_CS_RXERR | PCM_CS_TXERR | PCM_CS_RXCLR | PCM_CS_TXCLR |
    PCM_CS_SYNC;
    sysPcm->cs |= PCM_CS_TXON | PCM_CS_EN;
//    while ((sysPcm->cs & PCM_CS_SYNC) == 0)
//	;
//    setGPIO(5, HIGH);

    play();
}

void play(){
    double ph = 0.0;
    static unsigned int fifoData = UINT_MAX;
    while (1){
	if (sysPcm->cs & PCM_CS_TXD){
	    // transmit data
	    // fifoData = (unsigned int)(UINT_MAX/2.0 * (1+dtcCos(ph)));
	    fifoData--;
	    ph += 2.0 * M_PI * mOutFreq / FS;
	    sysPcm->fifo = fifoData;
	}
    }

}
