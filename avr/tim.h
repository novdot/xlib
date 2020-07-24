/*
 * tim.h
 *
 * Created: 23.07.2020 16:27:04
 *  Author: 
 */ 


#ifndef TIM_H_
#define TIM_H_

typedef void (*handler_t)(void);

void tim_init(handler_t a_handler);

void __disable_irq();
void __enable_irq();

#endif /* TIM_H_ */