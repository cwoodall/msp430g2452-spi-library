//******************************************************************************
//  MSP430G2xx2 Demo - SPI full-Duplex 3-wire Master
//
//  Description: SPI Master communicates full-duplex with SPI Slave using
//  3-wire mode. The level on P1.4 is TX'ed and RX'ed to P1.0.
//  Master will pulse slave reset for synch start.
//  ACLK = n/a, MCLK = SMCLK = Default DCO
//
//                Slave                      Master
//             MSP430G2xx2          MSP430G2xx2
//             -----------------          -----------------
//            |              XIN|-    /|\|              XIN|-
//            |                 |      | |                 |
//            |             XOUT|-     --|RST          XOUT|-
//            |                 | /|\    |                 |
//            |          RST/NMI|--+<----|P1.2             |
//      LED <-|P1.0             |        |             P1.4|<-
//          ->|P1.4             |        |             P1.0|-> LED
//            |         SDI/P1.7|<-------|P1.6/SDO         |
//            |         SDO/P1.6|------->|P1.7/SDI         |
//            |        SCLK/P1.5|<-------|P1.5/SCLK        |
//
//  D. Dang
//  Texas Instruments Inc.
//  December 2010
//  Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************

//MODIFIED TO COMMUNICATE WITH THE AD5620

#include "spi/spi.h"
//#include "spi/ad5620.h"
#include "spi/ad5504.h"
#include "spi/dac7512.h"
/*
#define PIN_SCLK   BIT5 //1.5
#define PIN_MOSI   BIT6 //1.6
#define PIN_MISO   BIT7 //1.7
#define PIN_CS1    BIT4 //1.4
#define PIN_CS2	   BIT3 //1.3
*/


spi_device_t ad5504;
spi_device_t dac7512;

void main(void) {
	uint16_t dac7512_value = 0;
//	uint16_t ad5504_value = 0x01f;

	WDTCTL = WDTPW + WDTHOLD;            // disable WDT
	BCSCTL1 = CALBC1_16MHZ;               // 16MHz clock
	DCOCTL  = CALDCO_16MHZ;

	SPI_init();
	AD5504_init(&ad5504);
	DAC7512_init(&dac7512);
//	AD5620_init();

	AD5504_send(&ad5504, AD5504_CTRL, AD5504_CHA_ON|64, AD5504_WRITE);
	while (1) {
		if (dac7512_value < 0xfff) {
			dac7512_value += 1;
		} else {
			dac7512_value = 0;
		}
	//		ad5504_value = 0x8FF;
		
		//AD5504_send(&ad5504, AD5504_CHA, ad5504_value, AD5504_WRITE);
		DAC7512_send(&dac7512, dac7512_value);
		
		__delay_cycles(100);
 	}
}

