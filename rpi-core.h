/*
    Reference:
	Trying Bare Metal on Raspberry Pi 2. www.raspberrypi.org/forums/viewtopic.php?p=701773

    Huanle Zhang at UC Davis. www.huanlezhang.com
    Last Update: April 28, 2017
*/

#ifndef _RPI_CORE_H_
#define _RPI_CORE_H_

#define CORE1_START_ADDRESS 0x4000009C
#define CORE2_START_ADDRESS 0x400000AC
#define CORE3_START_ADDRESS 0x400000BC

extern _core_1_main;
extern _core_2_main;
extern _core_3_main;

void start_core_1(void);
void start_core_2(void);
void start_core_3(void);

extern volatile int pCoreRun[];

#endif
