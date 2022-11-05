/*
 * MC2.h
 * Author: Nardeen
 */


#include "uart.h"
#include "dc_motor.h"
#include "buzzer.h"
#include "external_eeprom.h"
#include "timer1.h"
#include "std_types.h"
#include "AVR/delay.h"
#include "twi.h"
#include "AVR/interrupt.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define PASSWORD_SIZE 5
#define MC_READY 0x10
#define SEND_PASSWORD 0x01
#define CONFIRM_PASSWORD 0x02
#define BUZZER_ON 0x03
#define OPEN_DOOR 0x04
#define MATCHED 0x05
#define NOT_MATCHED 0x06
#define DONE 0x07
#define EEPROM_ADDRRESS 0X301

uint8  g_password[5];
uint8 g_eeprom_password[5];
uint8 g_tick=0;
UART_ConfigType uart_Config_Ptr ={EIGHT_BIT, DISABLED,ONE_STOP_BIT,9600};
TWI_ConfigType twi_Config_Ptr= {0x01 , 0x02 , PRESCALER_1};



/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Function to read password from memory
 */
void readFromMemory(void);
/*
 * function to save password in memory
 */
void saveInMemory(void);
/*
 * function to recieve password from another Mc using uart
 */
void recievePassword(void);
/*
 * function check if the password is correct
 */
void checkPassword(void);
/*
 * Function to confirm that the MC is ready to recieve the bytes from other MC
 */
uint8 MCReceiveState(void);
/*
 * Function to check if the other MC is ready to recieve the bytes from this MC
 */
void MCSendState(uint8 MC_state);
/*
 * call back function for the timer 1 calculate g_tick++
 */
void timer_callBack();
/*
 * function to calculate any delay using timer 1
 */
void timer1_delay(int num);
