/*
    Reference: 
	Brian Sidebotham's Bare Metal Pi Tutorial. www.valvers.com
	Davis Welch's Pi Repo. www.github.com/dwelch67/raspberrypi
    
    
    Huanle Zhang at UC Davis. www.huanlezhang.com 
    Last Update: May 16, 2017

*/

#include "rpi-gpio.h"

const int gpio_pin[][2] = { // #register, #bit
  {0, 0}, // pin 0
  {0, 3}, // pin 1
  {0, 6}, // pin 2
  {0, 9}, // pin 3
  {0, 12}, // pin 4
  {0, 15}, // pin 5
  {0, 18}, // pin 6
  {0, 21}, // pin 7
  {0, 24}, // pin 8
  {0, 27}, // pin 9
  {1, 0}, // pin 10
  {1, 3}, // pin 11
  {1, 6}, // pin 12
  {1, 9}, // pin 13
  {1, 12}, // pin 14
  {1, 15}, // pin 15
  {1, 18}, // pin 16
  {1, 21}, // pin 17
  {1, 24}, // pin 18
  {1, 27}, // pin 19
  {2, 0}, // pin 20
  {2, 3}, // pin 21
  {2, 6}, // pin 22
  {2, 9}, // pin 23
  {2, 12}, // pin 24
  {2, 15}, // pin 25
  {2, 18}, // pin 26
  {2, 21}, // pin 27
  {2, 24}, // pin 28
  {2, 27}, // pin 29
  {3, 0}, // pin 30
  {3, 3}, // pin 31
  {3, 6}, // pin 32
  {3, 9}, // pin 33
  {3, 12}, // pin 34
  {3, 15}, // pin 35
  {3, 18}, // pin 36
  {3, 21}, // pin 37
  {3, 24}, // pin 38
  {3, 27}, // pin 39
  {4, 0}, // pin 40
  {4, 3}, // pin 41
  {4, 6}, // pin 42
  {4, 9}, // pin 43
  {4, 12}, // pin 44
  {4, 15}, // pin 45
  {4, 18}, // pin 46
  {4, 21}, // pin 47
  {4, 24}, // pin 48
  {4, 27}, // pin 49
  {5, 0}, // pin 50
  {5, 3}, // pin 51
  {5, 6}, // pin 52
  {5, 9}, // pin 53
};

volatile unsigned int* gpio = (unsigned int*)GPIO_BASE;

int setGPIOAlt(int pin, int alt){
    volatile static int synFlag = 0;
    while(synFlag == 1)
	;
    synFlag = 1;

    if (pin < 0 || pin > 53) return -1;
    if (alt < 0 || alt > 5) return -2;

    switch (alt){
	case 0:
	    gpio[GPIO_GPFSEL0 + gpio_pin[pin][0]] |= (1 << (gpio_pin[pin][1]+2));
	    gpio[GPIO_GPFSEL0 + gpio_pin[pin][0]] &= ~(1 << (gpio_pin[pin][1]+1));
	    gpio[GPIO_GPFSEL0 + gpio_pin[pin][0]] &= ~(1 << (gpio_pin[pin][1]+0));
	    break;
	case 1:
	    break;
	case 2:
	    break;
	case 3:
	    break;
	case 4:
	    break;
	case 5:
	    break;
	default:
	    synFlag = 0;
	    return -3;
    }

    synFlag = 0;
    return 0;
}

int setGPIOMode(int pin, int mode){
    
    volatile static int synFlag = 0;
    while(synFlag == 1)
	;
    synFlag = 1;
    if (pin < 0 || pin > 53) return -1;
    if (mode != INPUT && mode != OUTPUT) return -2;
    if (mode == INPUT){
	// 0 0 0
	gpio[GPIO_GPFSEL0 + gpio_pin[pin][0]] &= ~( 1 << gpio_pin[pin][1]);
	gpio[GPIO_GPFSEL0 + gpio_pin[pin][0]] &= ~( 1 << (gpio_pin[pin][1]+1) );
	gpio[GPIO_GPFSEL0 + gpio_pin[pin][0]] &= ~( 1 << (gpio_pin[pin][1]+2) );
    } else { // 0 0 1
	gpio[GPIO_GPFSEL0 + gpio_pin[pin][0]] |=  1 << gpio_pin[pin][1];
	gpio[GPIO_GPFSEL0 + gpio_pin[pin][0]] &= ~( 1 << (gpio_pin[pin][1]+1) );
	gpio[GPIO_GPFSEL0 + gpio_pin[pin][0]] &= ~( 1 << (gpio_pin[pin][1]+2) );
    }
    synFlag = 0;
    return 0;
}

int setGPIOEvent(int pin, int event){
    volatile static int synFlag = 0;
    while (synFlag == 1)
	;
    synFlag = 1;

    if (pin < 0 || pin > 53) return -1;
    switch (event){
    case GPIO_EVENT_R:
	if (pin <= 31){
	    gpio[GPIO_GPREN0] |= (1 << pin);    
	} else {
	    gpio[GPIO_GPREN1] |= (1 << (pin - 32));
	}
	break;
    }

    synFlag = 0;
    return 0;
}

inline void disableGPIOEvent(int pin, int event){
    switch (event){
	case GPIO_EVENT_R:
	    if (pin <= 31){
		gpio[GPIO_GPREN0] &= ~(1 << pin);	
	    } else {
		gpio[GPIO_GPREN1] &= ~(1 << (pin - 32));	
	    }
	    break;
    }
    return;
}

inline int isGPIOEventDetected(int pin){
    if (pin <= 31){
	return (gpio[GPIO_GPEDS0] & (1 << pin)) != 0 ? 1 : 0; 
    } else {
	return (gpio[GPIO_GPEDS1] & (1 << (pin - 32))) != 0 ? 1 : 0;
    }
    return -1;
}

inline void clearGPIOEvent(int pin){
    if (pin <= 31){
	gpio[GPIO_GPEDS0] |= 1 << pin;	
    } else {
	gpio[GPIO_GPEDS1] |= 1 << (pin - 32);
    }    
    return;
}

inline void setGPIOPin(int pin, int status){
    
    if (status == HIGH){
	if (pin <= 31){
	    gpio[GPIO_GPSET0] = 1 << pin;    
	} else {
	    gpio[GPIO_GPSET1] = 1 << (pin - 32);
	}	
    } else { // low
    	if (pin <= 31){
	    gpio[GPIO_GPCLR0] = 1 << pin;
	} else {
	    gpio[GPIO_GPCLR1] = 1 << (pin - 32);
	}
    }

    return;
}

int setGPIO(int pin, int status){
    
    volatile static int synFlag = 0;
    while(synFlag == 1){
	;
    }
    synFlag = 1;

    if (pin < 0 || pin > 53) return -1;
    if (status != HIGH && status != LOW) return -2;

    gpio[GPIO_GPFSEL0 + gpio_pin[pin][0]] |= (1 << (gpio_pin[pin][1]));
    if (status == HIGH){
	if (pin <= 31){
	    gpio[GPIO_GPSET0] = (1 << pin);   
	} else { 
	    gpio[GPIO_GPSET1] = (1 << (pin - 32));    
	}
    } else {
	if (pin <= 31){
	    gpio[GPIO_GPCLR0] = (1 << pin);    
	} else {
	    gpio[GPIO_GPCLR1] = (1 << (pin - 32));    
	}	
    }

    synFlag = 0;
    return 0;
}

inline int readGPIO(int pin){
    
    if (pin <= 31){
	if ((gpio[GPIO_GPLEV0] & (1 << pin)) != 0){
	    return HIGH;    
	} else {
	    return LOW;    
	}
    } else {
	if ((gpio[GPIO_GPLEV1] & (1 << (pin - 32))) != 0){
	    return HIGH;    
	} else {
	    return LOW;    
	}
    }
    return -1;
}
