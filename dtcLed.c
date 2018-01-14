/*
 *
 * Huanle Zhang at UC Davis
 * www.huanlezhang.com
 *
 */

/* 
 * This file for LED demonstration only...
 */

#include "rpi-gpio.h"
#include "dtcLed.h"

volatile int dtcLedCtrl_1 = 0;

void initLeds(void){

	// set rgb ports to output
	setGPIOMode(DTC_R_PIN, OUTPUT);
	setGPIOMode(DTC_G_PIN, OUTPUT);
	setGPIOMode(DTC_B_PIN, OUTPUT);

}

// ugly codes below, but efficient
inline void pwmLed_R(const unsigned char pwm){
	static unsigned char prev = 0;
	static unsigned char sum = 0;
	if (prev != pwm){
		prev = pwm;
		sum = 0;
	}
	sum += pwm;
	if (sum >= 100){
		setGPIOPin(DTC_R_PIN, HIGH);
		sum -= 100;
	} else {
		setGPIOPin(DTC_R_PIN, LOW);
	}
}

inline void pwmLed_G(const unsigned char pwm){
	static unsigned char prev = 0;
	static unsigned char sum = 0;
	if (prev != pwm){
		prev = pwm;
		sum = 0;
	}
	sum += pwm;
	if (sum >= 100){
		setGPIOPin(DTC_G_PIN, HIGH);
		sum -= 100;
	} else {
		setGPIOPin(DTC_G_PIN, LOW);
	}
}

inline void pwmLed_B(const unsigned char pwm){
	static unsigned char prev = 0;
	static unsigned char sum = 0;
	if (prev != pwm){
		prev = pwm;
		sum = 0;
	}
	sum += pwm;
	if (sum >= 100){
		setGPIOPin(DTC_B_PIN, HIGH);
		sum -= 100;
	} else {
		setGPIOPin(DTC_B_PIN, LOW);
	}
}
