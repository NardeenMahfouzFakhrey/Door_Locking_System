/*
 * pwm.c
 * Author: Nardeen
 */


#include "pwm_timer0.h"

#include "avr/io.h"
#include "common_macros.h"

void PWM_Timer0_Start(uint8 duty_cycle){
	TCNT0=0;  //Set Timer Initial value
	OCR0=duty_cycle; // Set Compare Value

	SET_BIT(DDRB, PB3); //set PB3/OC0 as output pin
//	 Configure timer control register
//	 Fast PWM mode
//	 Clear OC0 when match occurs (non inverted mode)
//	 clock = F_CPU/8

	SET_BIT(TCCR0,WGM01);
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,COM01);
	SET_BIT(TCCR0, CS01);

}
