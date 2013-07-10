/*
 * spi.c
 *
 *  Created on: Jun 21, 2013
 *      Author: Christopher Woodall
 */
#include "spi/spi.h"
#include <msp430g2452.h>
#include <stdint.h>

void SPI_init()
{
	P1DIR   |=  PIN_MOSI + PIN_SCLK;
	P1DIR 	&= ~PIN_MISO;

	//// setup SPI
	USICTL0   |= USISWRST;                     // put USI in reset mode, source USI clock from SMCLK
	USICTL0  |= USIPE5 | USIPE6 | USIPE7 | USIMST | USIOE | USIGE;
	USICKCTL  |= USIDIV_1 | USISSEL_2;         // default speed 16MHz/1
	USICTL1    |= USICKPH;                      // SPI_MODE_0, CPHA=0
	USICKCTL  &= ~USICKPL;       // CPOL=0
	USICTL0  &= ~USILSB;       // MSBFIRST
	USICTL0  &= ~USISWRST;           // release for operation
}

/**
 * Set the SPI mode, spi.h defines SPI_MODE_[0..3] and CPHA_bit and CPOL_but for use in configuration
 */
inline void SPI_set_mode(uint8_t spi_mode) {
	if (spi_mode & CPHA_bit) {
		USICTL1    &= ~USICKPH;                      // CPHA=1
	} else {
		USICTL1    |= USICKPH;                      // CPHA=0
	}

	if (spi_mode & CPOL_bit) {
		USICKCTL  |= USICKPL;       // CPOL=1
	} else {
		USICKCTL  &= ~USICKPL;       // CPOL=0
	}
}

/**
 * Generic function for sending SPI data, relatively slow throughput with this
 * particular method because SPI mode gets set every time a spi send occurs.
 */
void SPI_send(spi_device_t *spi_dev, uint32_t value, uint16_t cs_arg) {
	int bits_sent = 0;
	SPI_set_mode(spi_dev->spi_mode);
	spi_dev->chip_select(cs_arg);
	int bits_to_send = 0;
	while (bits_sent < spi_dev->bits) {
		bits_to_send = (((spi_dev->bits)-bits_sent) >= 16)?16:((spi_dev->bits)-bits_sent);
		USISR = value >> bits_sent;
		USICNT = (USI16B | bits_to_send);
		while (!(USICTL1&USIIFG));
		bits_sent += bits_to_send;
	}
	__delay_cycles(2);
	spi_dev->chip_release(cs_arg);
}
