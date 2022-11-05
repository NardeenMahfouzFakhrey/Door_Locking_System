/*
 * DC Motor.c
 * Author: Nardeen
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define MOTOR_PORT_ID    PORTB_ID
#define MOTOR_PIN_EN_ID  PIN3_ID
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

/* function to initialize dc motor pin as output */

void DcMotor_Init(void);

/*function to determine direction of rotation of motor and control its speed */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DC_MOTOR_H_ */
