/*
 * buzzer.c
 * Author: Nardeen
 */
#include "gpio.h"
#include "buzzer.h"

 /*
 *Description
 *1-Setup the direction for the buzzer pin as output pin through the
 *GPIO driver.
 *2-Turn off the buzzer through the GPIO.
 */
void Buzzer_init() {
	GPIO_setupPinDirection(BUZZER_PORT_ID,BUZZER_PIN_ID, PIN_OUTPUT);
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID , LOGIC_LOW);
}
/*
 * -Description
 *Function to enable the Buzzer through the GPIO.
 */

void Buzzer_on(void){
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID , LOGIC_HIGH);
}

/*
 *- Description
 *Function to disable the Buzzer through the GPIO
 */

void Buzzer_off(void){
	GPIO_writePin(BUZZER_PORT_ID,BUZZER_PIN_ID , LOGIC_LOW);
}


