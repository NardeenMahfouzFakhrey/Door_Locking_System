/*
 * timer1.h
 * Author: Nardeen
 */

#ifndef TIMER1_H_
#define TIMER1_H_
#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
typedef enum{
NO_CLK ,F_CPU_1,F_CPU_8
	,F_CPU_64 , F_CPU_256, F_CPU_1024 ,EXTERNAL_CLK_FAILLING_EDGE  , EXTERNAL_CLK_RAISING_EDGE
}Timer1_Prescaler;

typedef enum {
	NORMAL_MODE , COMPARE_MODE
}Timer1_Mode;

typedef enum {
	NORMAL , TOGGLE , CLEAR ,SET
}Timer1_PIN_OPERATION;
typedef struct {
 uint16 initial_value;
 uint16 compare_value; // it will be used in compare mode only.
 Timer1_Prescaler prescaler;
 Timer1_Mode mode;
 Timer1_PIN_OPERATION pin_operation;

} Timer1_ConfigType;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Function to initialize the Timer driver
 *Inputs: pointer to the configuration structure with type
 *Timer1_ConfigType */
void Timer1_init(const Timer1_ConfigType * Config_Ptr);

/* Function to disable the Timer1 */
void Timer1_deInit(void);

/*
 *  Function to set the Call Back function address.
 *Inputs: pointer to Call Back function.
 */

void Timer1_setCallBack(void(*a_ptr)(void));

#endif /* TIMER1_H_ */
