/*

    Huanle Zhang at UC Davis. www.huanlezhang.com
    Last Update: May 16, 2017

*/

#ifndef _RPI_SERIAL_H_
#define _RPI_SERIAL_H_

int initSerial(int ckPin, int txPin, int rxPin);
int readSerial(void);
#endif
