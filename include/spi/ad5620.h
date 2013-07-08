/*
 * ad5620.h
 *
 *  Created on: Jun 21, 2013
 *      Author: Admin
 */

#ifndef AD5620_H_
#define AD5620_H_
#include <msp430g2452.h>
#include <stdint.h>
#include "spi/spi.h"

#define PIN_CS2 BIT3
void AD5620_init();

void AD5620_send(uint16_t value);


#endif /* AD5620_H_ */
