/*
 * timer1.c
 * Author: Nardeen
 */

#include "timer1.h"
#include <avr/io.h>
#include <avr/interrupt.h>

/* global pointer to function usef for call back */

static volatile void (*g_callBackPtr)(void)=NULL_PTR;


ISR(TIMER1_COMPA_vect){

	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application  */
		(*g_callBackPtr)();
	}

}
ISR(TIMER1_OVF_vect){

	if(g_callBackPtr != NULL_PTR)
		{
			/* Call the Call Back function in the application  */
			(*g_callBackPtr)();
		}
}

/*
 * Function to initialize the Timer driver
 *Inputs: pointer to the configuration structure with type
 *Timer1_ConfigType */

void Timer1_init(const Timer1_ConfigType * Config_Ptr){
	TCCR1A= (1<<FOC1A);
	TCCR1B = (Config_Ptr->mode << WGM12) | (Config_Ptr->prescaler << CS10);
	TCNT1= Config_Ptr->initial_value;
	OCR1A = Config_Ptr-> compare_value;
	TIMSK |=(1<<OCIE1A);
}

/* Function to disable the Timer1 */
void Timer1_deInit(void){
  TCCR1A=0;
  TCCR1B=0;
  TCNT1=0;
  TIMSK=0;

}

/*
 *  Function to set the Call Back function address.
 *Inputs: pointer to Call Back function.
 */

void Timer1_setCallBack(void(*a_ptr)(void)){
	g_callBackPtr = a_ptr;


}


