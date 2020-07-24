/*
 * tim.c
 * this code sets up timer1
 * Created: 23.07.2020 16:27:16
 *  Author: 
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>

#include "xlib/avr/tim.h"
#include "xlib/avr/compilers.h"

handler_t g_handler;

/*****************************************************************************/
void tim_init(handler_t a_handler)
{
	g_handler = a_handler;
	
	/*
	CS10 and CS12 div = 1024
	1/(16 ? 10^6 / 1024) = (6.4e-5 s) for 16MHz
	
	(target time) = (timer resolution) * (# timer counts + 1)

	(# timer counts + 1) = (target time) / (timer resolution)
	(# timer counts + 1) = (1 s) / (6.4e-5 s)
	(# timer counts + 1) = 15625
	(# timer counts) = 15625 - 1 = 15624 //15624 for 1 sec; 
	
	cnt = (period_s / 1024)*F_CPU - 1
	*/
	
	x_uint8_t period_ms = 100;
	
	// установить TCCR1A регистр в 0
	TCCR1A = 0;
	TCCR1B = 0;
	
	// установка регистра совпадения
	OCR1A = (period_ms/1024)*(F_CPU/1000);
	// включение в CTC режим
	TCCR1B |= (1 << WGM12);

	// Установить CS10 бит так, чтобы таймер работал при тактовой частоте:
	TCCR1B |= (1 << CS10);
	// Установка битов CS10 и CS12 на коэффициент деления 1024
	TCCR1B |= (1 << CS12);
	
	// включение прерываний по совпадению
	TIMSK1 |= (1 << OCIE1A);  
}

/*****************************************************************************/
ISR (TIMER1_OVF_vect) 
{
	//overflow
}
ISR(TIMER1_COMPA_vect)
{
	__disable_irq();
	g_handler();
	__enable_irq();
}
/*****************************************************************************/
void __disable_irq()
{
	cli();
	wdt_disable();
}
/*****************************************************************************/
void __enable_irq()
{
	sei();
}
/*****************************************************************************/