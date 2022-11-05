/*
 * dc_motor.c
 * Author: Nardeen
 */

#include "dc_motor.h"
#include "gpio.h"
#include "pwm_timer0.h"

/* function to initialize dc motor pin as output */

void DcMotor_Init(void){
	GPIO_setupPinDirection( MOTOR_PORT_ID,MOTOR_PIN_IN1_ID ,PIN_OUTPUT);
	GPIO_setupPinDirection( MOTOR_PORT_ID,MOTOR_PIN_IN2_ID ,PIN_OUTPUT);

	GPIO_writePin( MOTOR_PORT_ID,MOTOR_PIN_IN1_ID,LOGIC_LOW);
	GPIO_writePin( MOTOR_PORT_ID,MOTOR_PIN_IN2_ID,LOGIC_LOW);
}
/*function to determine direction of rotation of motor and control its speed */

void DcMotor_Rotate(DcMotor_State state,uint8 speed){
	    uint8 duty_cycle=((float)speed/100)*255;
		PWM_Timer0_Start(duty_cycle);

	if(state==STOP){
			GPIO_writePin(MOTOR_PORT_ID,MOTOR_PIN_IN1_ID,LOGIC_LOW);
			GPIO_writePin(MOTOR_PORT_ID,MOTOR_PIN_IN2_ID,LOGIC_LOW);

		}else if(state==CLOCKWISE){
			GPIO_writePin(MOTOR_PORT_ID,MOTOR_PIN_IN1_ID,LOGIC_HIGH);
			GPIO_writePin(MOTOR_PORT_ID,MOTOR_PIN_IN2_ID,LOGIC_LOW);
		}else{
			GPIO_writePin(MOTOR_PORT_ID,MOTOR_PIN_IN1_ID,LOGIC_LOW);
			GPIO_writePin(MOTOR_PORT_ID,MOTOR_PIN_IN2_ID,LOGIC_HIGH);
		}


}

