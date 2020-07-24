/*
 * spi.c
 *
 * Created: 14.07.2020 13:28:14
 *  Author: 
 */ 

#include "xlib/avr/spi.h"
#include "xlib/avr/compilers.h"

#define SPI_PORTX   PORTB
#define SPI_DDRX    DDRB

#define SPI_MISO   6
#define SPI_MOSI   5
#define SPI_SCK    7

/*****************************************************************************/
void spi_init(uint16_t a_CsPinMask)
{
	int ipin = 0;
	//настройка портов ввода-вывода все выводы, кроме MISO выходы
	SPI_DDRX |= (1<<SPI_MOSI)|(1<<SPI_SCK)|(0<<SPI_MISO)|(a_CsPinMask);
	SPI_PORTX |= (1<<SPI_MOSI)|(1<<SPI_SCK)|(1<<SPI_MISO)|(a_CsPinMask);
	
	//разрешение spi,старший бит вперед,мастер, режим 0
	SPCR = (1<<SPE)|(0<<DORD)|(1<<MSTR)|(0<<CPOL)|(0<<CPHA)|(1<<SPR1)|(0<<SPR0);
	SPSR = (0<<SPI2X);
}

/*****************************************************************************/
void spi_write(uint8_t a_pin,uint8_t* a_pdata, uint16_t a_size)
{
	SPI_PORTX &= ~(1<<a_pin);
	while(a_size--){
		SPDR = *a_pdata++;
		while(!(SPSR & (1<<SPIF)));
	}
	SPI_PORTX |= (1<<a_pin);
}

/*****************************************************************************/
void spi_read(uint8_t a_pin,uint8_t* a_pdata, uint16_t a_size)
{
	SPI_PORTX &= ~(1<<a_pin);
	while(a_size--){
		SPDR = *a_pdata;
		while(!(SPSR & (1<<SPIF)));
		*a_pdata++ = SPDR;
	}
	SPI_PORTX |= (1<<a_pin);
}

/*****************************************************************************/