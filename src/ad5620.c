/*
 * ad5620.c
 *
 *  Created on: Jun 21, 2013
 *      Author: Admin
 */
#include <msp430g2452.h>
#include <stdint.h>
#include "spi/ad5620.h"

void AD5620_init()
{
	P1DIR   |= PIN_CS2;
	DESELECT(PIN_CS2);
}

void AD5620_send(uint16_t value)
{
	USISR = value<<2;
	SELECT(PIN_CS2);
	USICNT = USI16B | 16;

	while (!(USICTL1 & USIIFG));
	__delay_cycles(10);
	DESELECT(PIN_CS2);
}
