/*
 * adc.c
 *
 *  Created on: 8 Oct 2022
 *      Author: Nardeen
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define MOTOR_PORT_ID  PORTB_ID
#define MOTOR_PIN_EN_ID PIN3_ID
#define MOTOR_PIN_IN1_ID PIN0_ID
#define MOTOR_PIN_IN2_ID PIN1_ID

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

typedef enum
{
	STOP,CLOCKWISE,ANTI_CLOCKWISE
}DcMotor_State;

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DC_MOTOR_H_ */
