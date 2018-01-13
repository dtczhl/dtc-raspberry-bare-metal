/*

    Huanle Zhang at UC Davis. www.huanlezhang.com
    Last Update: May 25, 2017

*/

#include "rpi-networking.h"
#include "rpi-serial.h"
#include "rpi-gpio.h"
#include "dtcMediaPlayer.h"

static const int mCkPin = 2;
static const int mTxPin = 3;
static const int mRxPin = 4;

static const int CMD_PLAY = 0x00;
static const int CMD_STOP = 0x40;
static const int CMD_PREV = 0x80;
static const int CMD_NEXT = 0xC0;

static const int VOL_MIN = 0;
static const int VOL_MAX = 63;

void startNetworking(void){
    
    int readData = 0;
    volatile static int flag[5] = {0, 0, 0, 0, 0};

    initSerial(mCkPin, mTxPin, mRxPin);

    while (1){
	readData = readSerial();
	
	if (readData <= 0x3F && readData != 0){ // volume data
	   
	  // flag[0] = 1 - flag[0];
	  // setGPIO(6, flag[0]);
	    mediaPlayer_vol(readData);

	} else if (readData == CMD_PLAY){ // play
	    
	    //setGPIO(13, HIGH);
	    mediaPlayer_start();
	    
	} else if (readData == CMD_STOP){ // stop
	
	    //setGPIO(13, LOW);
	    mediaPlayer_stop();

	} else if (readData == CMD_PREV){ // prev
	    
	    //flag[3] = 1 - flag[3];
	    //setGPIO(19, flag[3]);
	    mediaPlayer_prev();
	} else if (readData == CMD_NEXT){ // next
	    //flag[4] = 1 - flag[4];
	    //setGPIO(26, flag[4]);
	    mediaPlayer_next();
	}

    }

}
