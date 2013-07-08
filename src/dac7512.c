/*
 * dac7512.c
 *
 *  Created on: Jun 21, 2013
 *      Author: Admin
 */
#include <msp430g2452.h>
#include <stdint.h>
#include "spi/spi.h"
#include "spi/dac7512.h"
void DAC7512_init(spi_device_t *dev) {
	P1DIR |= BIT3;
	dev->bits = 16;
	dev->spi_mode = SPI_MODE_2;
	dev->delay_cycles = 10;
	dev->chip_select  = *DAC7512_chip_select;
	dev->chip_release = *DAC7512_chip_release;
}
void DAC7512_send(spi_device_t *dev, uint16_t data) {
	SPI_send(dev, data, 1);
}

void DAC7512_chip_select(uint16_t cs_arg) {
	SELECT(BIT3);
}

void DAC7512_chip_release(uint16_t cs_arg) {
	DESELECT(BIT3);
}
