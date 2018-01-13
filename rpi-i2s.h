/*
    Reference:
	DMA and SPI and Interrupts - cannot get it to work.
	www.raspberrypi.org/forums/viewtopic.php?f=71&t=19797


    Huanle Zhang at UC Davis. www.huanlezhang.com
    Last Update: April 28, 2017

    Under testing...

*/

#ifndef _RPI_PCM_H_
#define _RPI_PCM_H_

#include "dtcArgs.h"

#define PCM_CLK	    18
#define PCM_FS	    19
#define PCM_DIN	    20
#define PCM_DOUT    21

#define PCM_CLK_GPIO_ALT	0
#define PCM_FS_GPIO_ALT		0
#define PCM_DIN_GPIO_ALT	0
#define PCM_DOUT_GPIO_ALT	0

#define PCM_CS_STBY	( 1 << 25 )
#define PCM_CS_SYNC	( 1 << 24 )
#define PCM_CS_RXSEX	( 1 << 23 )
#define PCM_CS_RXF	( 1 << 22 )
#define PCM_CS_TXE	( 1 << 21 )
#define PCM_CS_RXD	( 1 << 20 )
#define PCM_CS_TXD	( 1 << 19 )
#define PCM_CS_RXR	( 1 << 18 )
#define PCM_CS_TXW	( 1 << 17 )
#define PCM_CS_RXERR	( 1 << 16 )
#define PCM_CS_TXERR	( 1 << 15 )
#define PCM_CS_RXSYNC	( 1 << 14 )
#define	PCM_CS_TXSYNC	( 1 << 13 )
// 13 - 10 reserved
#define PCM_CS_DMAEN	( 1 << 9 )
#define PCM_CS_RXTHR_S	( 0 << 7 )
#define PCM_CS_RXTHR_LF ( 1 << 7 )
#define PCM_CS_RXTHR_L	( 2 << 7 )
#define PCM_CS_RXTHR_F	( 3 << 7 )
#define PCM_CS_TXTHR_S	( 0 << 5 )
#define PCM_CS_TXTHR_LF	( 1 << 5 )
#define PCM_CS_TXTHR_L	( 2 << 5 )
#define PCM_CS_TXTHR_F	( 3 << 5 )
#define PCM_CS_RXCLR	( 1 << 4 )
#define PCM_CS_TXCLR	( 1 << 3 )
#define	PCM_CS_TXON	( 1 << 2 )
#define PCM_CS_RXON	( 1 << 1 )
#define PCM_CS_EN	( 1 << 0 )

#define PCM_MOD_CLK_DIS ( 1 << 28 )
#define PCM_MOD_PDWN	( 1 << 27 )
#define	PCM_MOD_PDME	( 1 << 26 )
#define PCM_MOD_FRXP	( 1 << 25 )
#define PCM_MOD_FTXP	( 1 << 24 )
#define PCM_MOD_CLKM	( 1 << 23 )
#define PCM_MOD_CLKI	( 1 << 22 )
#define PCM_MOD_FSM	( 1 << 21 )
#define	PCM_MOD_FSI	( 1 << 20 )
#define PCM_MOD_FLEN_BIT 10
#define PCM_MOD_FSLEN_BIT 0

// omit RXC register

#define PCM_TXC_CH1WEX	( 1 << 31 )
#define PCM_TXC_CH1EN	( 1 << 30 )
#define PCM_TXC_CH1POS_BIT 20
#define	PCM_TXC_CH1WID_BIT  16
#define	PCM_TXC_CH2WEX	( 1 << 15 )
#define PCM_TXC_CH2EN	( 1 << 14 )
#define PCM_TXC_CH2POS_BIT 4
#define PCM_TXC_CH2WID_BIT 0

// omit DREQ register
// omit INTEN register
// omit INTSTC register
// omit GRAY register

typedef struct {
    volatile unsigned int cs;
    volatile unsigned int fifo;
    volatile unsigned int mode;
    volatile unsigned int rxc;
    volatile unsigned int txc;
    volatile unsigned int dreq;
    volatile unsigned int inten;
    volatile unsigned int intstc;
    volatile unsigned int gray;
} PCM_registers;

void startAudio();

#endif
