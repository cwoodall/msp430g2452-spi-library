/*
 * spi.h
 *
 *  Created on: Jun 21, 2013
 *      Author: Admin
 */

#ifndef SPI_H_
#define SPI_H_
#include <msp430g2452.h>
#include <stdint.h>
// Define location of PORT 1 SPI pins. Chip Select must be setup seperately.
#define PIN_SCLK   BIT5 //1.5
#define PIN_MOSI   BIT6 //1.6
#define PIN_MISO   BIT7 //1.7

#define SELECT(PIN)  P1OUT &= ~PIN
#define DESELECT(PIN)  P1OUT |= PIN

// The following code  is used to set the SPI mode
// All SPI mode information is referenced from [wikipedia][1]
// [1]: http://en.wikipedia.org/wiki/Serial_Peripheral_Interface_Bus
#define CPHA_bit   BIT1 // Set CPHA to 0 or 1
#define CPOL_bit   BIT2 // Set CPOL to 0 or 1
#define SPI_MODE_0 0x0 // SPI_MODE_0: CPOL = 0, CPHA = 0
#define SPI_MODE_1 0x2 // SPI_MODE_1: CPOL = 0, CPHA = 1
#define SPI_MODE_2 0x4 // SPI_MODE_2: CPOL = 1, CPHA = 0
#define SPI_MODE_3 0x6 // SPI_MODE_3: CPOL = 1, CPHA = 1
typedef struct spi_device {
	// What SPI mode does the device require
	uint8_t spi_mode;

	// How many bits to be sent
	uint8_t bits;

	// Number of cycles to delay
	uint8_t delay_cycles;

	// Function pointer to the function that gets called on chip select
	void (*chip_select)(uint16_t);
	// Function pointer to the function that gets called when a chip is released
	void (*chip_release)(uint16_t);
} spi_device_t ;


void SPI_init();
inline void SPI_set_mode(uint8_t spi_mode);
void SPI_send(spi_device_t *spi_dev, uint32_t value, uint16_t cs_arg);

#endif /* SPI_H_ */
