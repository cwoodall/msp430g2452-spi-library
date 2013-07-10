/**
 * ad5504.c : init, send, chip release and chip_select code for the
 * 			  [AD5504 datasheet][1]
 *
 * [1]: http://www.analog.com/static/imported-files/data_sheets/AD5504.pdf
 *
 *  Created on: Jun 21, 2013
 *      Author: Chris Woodall
 */
#include <msp430g2452.h>
#include <stdint.h>
#include "spi/spi.h"
#include "spi/ad5504.h"


/**
 * Initialize a spi_device_t struct for the AD5504. These settings are taken from the [datasheet][1]
 */
void AD5504_init(spi_device_t *dev) {
	P1DIR |= PIN_CS1; // Setup the chip select pins.
	dev->bits = 16; // According to datasheet messages to the AD5504 are 16 bits long
	dev->spi_mode = SPI_MODE_1; // According to the 5504 datasheet it looks like SPI mode 1.
								// Tested and verified by Jeff Kitteridge on July 9, 2013
	dev->delay_cycles = 10; 	// Currently unused
	dev->chip_select = *AD5504_chip_select;   // Set the chip select function pointer up
	dev->chip_release = *AD5504_chip_release; // Setup the chip release function pointer.
}

/**
 * Send function for the AD5504 which formats the 16, bit messages for the AD5504.
 * Message format is as follows:
 * +------++-----+--------------+-------------+
 * | Bits || 15  | 14 downto 12 | 11 downto 0 |
 * +======++=====+==============+=============+
 * | DOUT || R_W | Address 		| Data        |
 * +------++-----+--------------+-------------+
 */
void AD5504_send(spi_device_t *dev, uint8_t address, uint16_t value, uint8_t read_write) {

	SPI_send(dev, ((read_write | address) << 12) | (value & 0x0FFF), 1);
}

/**
 * Select chip.
 */
void AD5504_chip_select(uint16_t cs_arg) {
	SELECT(PIN_CS1);
}

/**
 * Deselect chip.
 */
void AD5504_chip_release(uint16_t cs_arg) {
	DESELECT(PIN_CS1);
}
