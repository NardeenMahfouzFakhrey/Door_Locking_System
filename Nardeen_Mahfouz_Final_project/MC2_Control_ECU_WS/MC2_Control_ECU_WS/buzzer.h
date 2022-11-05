/*
 * buzzer.h
 * Author: Nardeen
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define BUZZER_PORT_ID PORTC_ID //select buzzer port_ID
#define BUZZER_PIN_ID PIN3_ID // select pin_ID


/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

 /*
 *Description
 *1-Setup the direction for the buzzer pin as output pin through the
 *GPIO driver.
 *2-Turn off the buzzer through the GPIO.
 */
void Buzzer_init();
/*
 * -Description
 *Function to enable the Buzzer through the GPIO.
 */

void Buzzer_on(void);
/*
 *- Description
 *Function to disable the Buzzer through the GPIO
 */

void Buzzer_off(void);

#endif /* BUZZER_H_ */