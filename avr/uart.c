/*
 * uart.c
 *
 * Created: 14.07.2020 13:28:32
 *  Author: NDA
 */ 

#include "xlib/avr/uart.h"
#include "xlib/avr/compilers.h"

#define BAUD 9600L // Скорость обмена данными
#define UBRRL_value (F_CPU/(BAUD*16))-1 //Согластно заданной скорости подсчитываем значение для регистра UBRR

/*****************************************************************************/
void uart_init()
{
	UBRR0L = UBRRL_value & 0xFF;
	UBRR0H = UBRRL_value >> 8;
	/*Enable receiver and transmitter */
	UCSR0B |= (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 1stop*/
	UCSR0C = (3<<UCSZ00);
}

/*****************************************************************************/
void uart_send_byte(x_uint8_t value)
{
	// Ожидаем когда очистится буфер передачи
	while(!(UCSR0A & (1 << UDRE0)));
	// Помещаем данные в буфер, начинаем передачу
	UDR0 = value;
}

/*****************************************************************************/
void uart_send(x_uint8_t* data,x_uint16_t size)
{
	while(*data > 0) uart_send_byte(*data++);
}

/*****************************************************************************/
x_uint8_t uart_read_byte()
{
	// wait for data
	while(!(UCSR0A & (1 << RXC0)));

	// return data
	return UDR0;
}

/*****************************************************************************/
void uart_read(x_uint8_t* buf, uint8_t n)
{
	uint8_t bufIdx = 0;
	char c;

	// while received character is not carriage return
	// and end of buffer has not been reached
	do {
		// receive character
		c = uart_read_byte();

		// store character in buffer
		buf[bufIdx++] = c;
	}
	while((bufIdx < n) && (c != '\r'));

	// ensure buffer is null terminated
	buf[bufIdx] = 0;
}