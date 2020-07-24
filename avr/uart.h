#ifndef __XLIB_AVR_UART_H_INCLUDED
#define __XLIB_AVR_UART_H_INCLUDED

#include "xlib/types.h"

#if defined(DEBUG)
#define DBG(_buf,_msg,_size) \
	memset(_buf,0,_size); \
	sprintf(_buf,_msg); \
	uart_send(_buf,_size);

#define DBG1(_buf,_msg,_par1,_size) \
	memset(_buf,0,_size); \
	sprintf(_buf,_msg,_par1); \
	uart_send(_buf,_size);
	
#define DBG2(_buf,_msg,_par1,_par2,_size) \
	memset(_buf,0,_size); \
	sprintf(_buf,_msg,_par1,_par2); \
	uart_send(_buf,_size);
#else //__DEBUG__
#define DBG(_buf,_msg,_size) 0
#define DBG1(_buf,_msg,_par1,_size) 0
#define DBG2(_buf,_msg,_par1,_par2,_size) 0
#endif

void uart_init();
void uart_send_byte(x_uint8_t value);
void uart_send(x_uint8_t* data,x_uint16_t size);
void uart_read(x_uint8_t* buf, uint8_t n);

#endif //__XLIB_AVR_UART_H_INCLUDED