/*

    Huanle Zhang at UC Davis. www.huanlezhang.com
    Last Update: June 8, 2017

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dtcMediaPlayer.h"
#include "rpi-gpio.h"
#include "rpi-pwm.h"
#include "audio_1.h"
#include "audio_2.h"
#include "audio_3.h"

volatile int pending_start = 0;
volatile int pending_stop = 0;
volatile int pending_prev = 0;
volatile int pending_next = 0;

volatile int pending_vol = 0;
volatile int volValue = 0;

char pMusicArray[PWM_BUFFER_SIZE];


inline void mediaPlayer_start(void){
    pending_start = 1;
}


inline void mediaPlayer_stop(void){
    pending_stop = 1;
}

inline void mediaPlayer_prev(void){
    pending_prev = 1;
}

inline void mediaPlayer_next(void){
    
    pending_next = 1;
}

inline void mediaPlayer_vol(int vol){
    pending_vol = 1;
    volValue = vol;
}

void startMediaPlayer(void){

    int size_buffer = 0;
    int i = 0;
    char data = 0;
    int index_audio_data = 0;
    int index_audio_file = 0;

    while (pwmInitialized() == -1)
	;
   
    pwmInitBuffer(pMusicArray);

    setGPIO(6, HIGH);

    while(1){
	if (pending_start != 0){
	    pending_start = 0;

	    setGPIO(13, HIGH);    
	    pwmResume();
	    continue;
	}
	if (pending_stop != 0){
	    pending_stop = 0;
	    setGPIO(13, LOW);

	    pwmStop();
	    continue;
	}
	if (pending_prev != 0){
	    pending_prev = 0;
	    setGPIO(19, HIGH); 

	    if (index_audio_file == 0)
		index_audio_file = 3;
	    
	    --index_audio_file;

	    index_audio_data = 0;
	    
	    continue;
	}
	if (pending_next != 0){
	    pending_next = 0;
	    setGPIO(19, LOW);

	    ++index_audio_file;
	    if (index_audio_file == 3)
		index_audio_file = 0;
	    
	    index_audio_data = 0;

	    continue;
	}
	if (pending_vol != 0){
	    pending_vol = 0;
	    // pwmSetVol(volValue / 63.0);
	    continue;
	}

	if (pwmBufferWritable() == 1){
	    if (index_audio_file == 0){
		for (i = 0; i < PWM_BUFFER_SIZE; i++){
		    // pMusicArray[i] = rand() % 256;
		    pMusicArray[i] = audio_data1[index_audio_data];
		    index_audio_data++;
		    index_audio_data %= AUDIO_1_LEN;
		}
	    } else if (index_audio_file == 1){
		for (i = 0; i < PWM_BUFFER_SIZE; i++){
		    pMusicArray[i] = audio_data2[index_audio_data];    
		    index_audio_data++;
		    index_audio_data %= AUDIO_2_LEN;
		}	
	    } else if (index_audio_file == 2){
		for (i = 0; i < PWM_BUFFER_SIZE; i++){
		    pMusicArray[i] = audio_data3[index_audio_data];
		    index_audio_data++;
		    index_audio_data %= AUDIO_3_LEN;
		}	
	    }
	    pwmAddBuffer();    
	}

    }    
}
