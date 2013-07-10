/**
 * MSP430G2452 - SPI full Duplex library test
 * C. Woodall
 * Boston University - NASA MUX
 * June 2013
 */
#include "spi/spi.h"
#include "spi/ad5504.h"
#include "spi/dac7512.h"
#include "math.h"

spi_device_t ad5504;
spi_device_t dac7512;

void main(void) {
	uint16_t dac7512_value = 0xfff;
	uint16_t ad5504_value = 0xfff;

	WDTCTL = WDTPW + WDTHOLD;            // disable WDT
	BCSCTL1 = CALBC1_1MHZ;               // 1MHz clock
	DCOCTL  = CALDCO_1MHZ;

	SPI_init();
	AD5504_init(&ad5504);
	DAC7512_init(&dac7512);

	AD5504_send(&ad5504, AD5504_CTRL, AD5504_CHA_ON|64, AD5504_WRITE);
	while (1) {
/*		if (dac7512_value < 0xfff) { // Uncomment to RAMP the dac7512
			dac7512_value += 1;
		} else {
			dac7512_value = 0;
		} */

/*		AD5504_send(&ad5504, AD5504_CHA, ad5504_value, AD5504_WRITE);
		DAC7512_send(&dac7512, dac7512_value);*/


		for (ad5504_value = 0; ad5504_value <= 0xfff; ad5504_value += 1) {
			AD5504_send(&ad5504, AD5504_CHA, ad5504_value, AD5504_WRITE);
			for (dac7512_value = 0; dac7512_value <= 0xfff; dac7512_value += 1) {
				DAC7512_send(&dac7512, dac7512_value);
				__delay_cycles(1);
			}
		}
 	}
}

