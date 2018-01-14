/*
 *
 * Huanle Zhang at UC Davis
 * www.huanlezhang.com
 *
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
