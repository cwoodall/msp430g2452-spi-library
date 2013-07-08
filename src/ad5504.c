/*
 * ad5504.c
 *
 *  Created on: Jun 21, 2013
 *      Author: Admin
 */
#include <msp430g2452.h>
#include <stdint.h>
#include "spi/spi.h"
#include "spi/ad5504.h"


void AD5504_init(spi_device_t *dev) {
	P1DIR |= PIN_CS1;

	dev->bits = 16;
	dev->spi_mode = 0;
	dev->delay_cycles = 10;
	dev->chip_select = *AD5504_chip_select;
	dev->chip_release = *AD5504_chip_release;
}

void AD5504_send(spi_device_t *dev, uint8_t address, uint16_t value, uint8_t read_write) {
	SPI_send(dev, ((read_write | address) << 12) | (value & 0x0FFF), 1);
}

void AD5504_chip_select(uint16_t cs_arg) {
	SELECT(PIN_CS1);
}

void AD5504_chip_release(uint16_t cs_arg) {
	DESELECT(PIN_CS1);
}
/*
void AD5504_init()
{
	P1DIR   |= PIN_CS1;
	DESELECT(PIN_CS1);
}

void AD5504_send(uint8_t address, uint16_t value, uint8_t read_write)
{
		USISR = ((read_write | address) << 12) | (value & 0x0FFF);
		SELECT(PIN_CS1);
		USICNT = USI16B | 16;

		while (!(USICTL1 & USIIFG));
		DESELECT(PIN_CS1);
}
*/
