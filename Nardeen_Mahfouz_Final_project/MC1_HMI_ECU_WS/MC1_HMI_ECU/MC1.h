/*
 * MC1.h
 * Author: Nardeen
 */

#ifndef MC1_H_
#define MC1_H_

#include "lcd.h"
#include "keypad.h"
#include "uart.h"
#include "timer1.h"
#include "AVR/delay.h"
#include "AVR/interrupt.h"
#include "AVR/io.h"

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
#define MAX_ERROR 3


uint8 g_password[5];
uint8 g_re_password[5];
uint8 g_eeprom_password[5];
uint8 g_tick=0;
uint8 g_error=0;
uint8 g_getkey;
UART_ConfigType Uart_Config_Ptr ={EIGHT_BIT, DISABLED,ONE_STOP_BIT,9600};

enum{
	CREATE_PASSWORD,CHANGE_PASSWORD,MAIN_MENU,ENTER_PASSWORD
};


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * function to calculate any delay using timer 1
 */
void timer1_delay(int num);
/*
 * function used to display on the lcd the mainmenu options
 */
void displayMainMenu();
/*
 * Function to control the door state with delays (locking , unlocking ,waiting)
 */

void openDoor();
/*
 * display on the screen that the password is incorrect
 */
void displayNotMatched(void);
/*
 * function to get the password from user from keypad and save to the array
 */
void getPassword(uint8 *key);
/*
 * function to send the saved password to the another MC using Uart
 */
void sendPassword(uint8* send_pass);
/*
 * Function to confirm that the MC is ready to recieve the bytes from other MC
 */
uint8 MCReceiveState(void);
/*
 * Function to check if the other MC is ready to recieve the bytes from this MC
 */
void MCSendState(uint8 MC_state);
/*
 * Function to display error on lcd for 1 min if number of trials exceed max errors
 */
void maxErrorOcurred();
/*
 * call back function for the timer 1 calculate g_tick++
 */
void timer_callBack();
/*
 * display on lcd enter password
 */
void displayEnterPassword();
/*
 * display on lcd re_enter password
 */
void displayRe_EnterPassword();
#endif /* MC1_H_ */
