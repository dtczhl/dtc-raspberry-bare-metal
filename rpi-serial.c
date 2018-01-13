/*

    Huanle Zhang at UC Davis. www.huanlezhang.com
    Last Update: May 22, 2017

*/

#include "rpi-serial.h"
#include "rpi-gpio.h"

static int mCkPin = 0, mTxPin = 0, mRxPin = 0;

int initSerial(int ckPin, int txPin, int rxPin){

    int serialPatternCount = 0;
    int compBit = 0, readBit = 0;
    const int SERIAL_COUNT_TARGET = 16;

    mCkPin = ckPin; mTxPin = txPin; mRxPin = rxPin;

    if (setGPIOMode(ckPin, INPUT) != 0) return -1;
    if (setGPIOMode(txPin, OUTPUT) != 0) return -1;
    if (setGPIOMode(rxPin, INPUT) != 0) return -1;
    if (setGPIOEvent(ckPin, GPIO_EVENT_R) != 0) return -1;

    while (serialPatternCount < SERIAL_COUNT_TARGET){
	
	while (!isGPIOEventDetected(mCkPin))
	    ;
	clearGPIOEvent(mCkPin);
	readBit = readGPIO(mRxPin);
	if (readBit != compBit){
	    serialPatternCount = 0;
	    continue;
	} 
	
	serialPatternCount++;	    
	compBit = 1 - compBit; 

    }

    // ACK
    setGPIOPin(mTxPin, HIGH);

    return 0;
}

int readSerial(void){

    // read 1 byte data, echo back

    int ret = 0;
    int readBit = 0;
    int i;

    for (i = 0; i < 8; i++) {
	
	while (!isGPIOEventDetected(mCkPin))
	    ;
	clearGPIOEvent(mCkPin);
	readBit = readGPIO(mRxPin);
	setGPIOPin(mTxPin, readBit);
	if (readBit == LOW){
	    ret = ret + (0 << i);    
	} else {
	    ret = ret + (1 << i);
	}
    }

    return ret;
}
