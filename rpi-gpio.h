/*
    Reference: 
	Brian Sidebotham's Bare Metal Pi Tutorial. www.valvers.com
	Davis Welch's Pi Repo. www.github.com/dwelch67/raspberrypi
    
    
    Huanle Zhang at UC Davis
	www.huanlezhang.com 

*/

#ifndef _RPI_GPIO_H_
#define _RPI_GPIO_H_

#include "rpiArgs.h"

#define GPIO_GPFSEL0 0
#define GPIO_GPFSEL1 1
#define GPIO_GPFSEL2 2
#define GPIO_GPFSEL3 3
#define GPIO_GPFSEL4 4
#define GPIO_GPFSEL5 5
// reserved - 6
#define GPIO_GPSET0 7
#define GPIO_GPSET1 8
// reserved - 9
#define GPIO_GPCLR0 10
#define GPIO_GPCLR1 11
// reserved - 12
#define GPIO_GPLEV0 13
#define GPIO_GPLEV1 14
// reserved - 15
#define GPIO_GPEDS0 16
#define GPIO_GPEDS1 17
// reserved - 18
#define GPIO_GPREN0 19
#define GPIO_GPREN1 20
// reserved - 21
#define GPIO_GPFEN0 22
#define GPIO_GPFEN1 23
// reserved - 24
#define GPIO_GPHEN0 25
#define GPIO_GPHEN1 26
// reserved - 27
#define GPIO_GPLEN0 28
#define GPIO_GPLEN1 29
// reserved - 30
#define GPIO_GPAREN0 31
#define GPIO_GPAREN1 32
// reserved - 33
#define GPIO_GPAFEN0 34
#define GPIO_GPAFEN1 35
// reserved - 36
#define GPIO_GPPUD 37
#define GPIO_GPPUDCLK0 38
#define GPIO_GPPUDCLK1 39
// reserved - 40
// test - 41

#define HIGH 1
#define LOW 0

#define INPUT 0
#define OUTPUT 1

#define GPIO_EVENT_R 0

int setGPIO(int pin, int status);
inline void setGPIOPin(int pin, int status);
inline int readGPIO(int pin);
int setGPIOMode(int pin, int status);
inline int setGPIOEvent(int pin, int event);
int setGPIOAlt(int pin, int alt);
inline int isGPIOEventDetected(int pin);
inline void clearGPIOEvent(int pin);
inline void disableGPIOEvent(int pin, int event);
#endif
