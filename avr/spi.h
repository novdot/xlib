#ifndef __XLIB_AVR_SPI_H_INCLUDED
#define __XLIB_AVR_SPI_H_INCLUDED

#include "xlib/types.h"

#define CS_DAC_x 10
#define CS_DAC_y 9
#define CS_DAC_z 8

void spi_init(uint16_t a_CsPinMask);
void spi_write(uint8_t a_pin,uint8_t* a_pdata, uint16_t a_size);
void spi_read(uint8_t a_pin,uint8_t* a_pdata, uint16_t a_size);

#endif //__XLIB_AVR_SPI_H_INCLUDED