/*
 * MC1.c
 *
 *  Created on: 30 Oct 2022
 *      Author: EES
 */

#include "MC1.h"

uint8 g_state = CREATE_PASSWORD;



int main(){

	UART_init(&Uart_Config_Ptr); //initialize uart
	LCD_init(); // lcd initialization
	SREG |= (1<<7); // enable interrupts

	while(1)
	{
		switch (g_state){
        /*
         * start state for creation a new password or change password
         */
		case CREATE_PASSWORD:
		{
			displayEnterPassword();
			getPassword(g_password);
			LCD_clearScreen();
			displayRe_EnterPassword();
			getPassword(g_re_password);
			MCSendState(SEND_PASSWORD);
			sendPassword(g_password);
			MCSendState(CONFIRM_PASSWORD);
			sendPassword(g_re_password);

			_delay_ms(500);
			uint8 s = MCReceiveState();
			if(s==MATCHED ){
				LCD_clearScreen();
				LCD_displayString("Matched");
				_delay_ms(200);
				g_state = MAIN_MENU;
			}
			else g_state=CREATE_PASSWORD;
		}

		break;
      /*
       * case for mainMenu options either open door or change pass
       */
		case MAIN_MENU:{

			g_getkey=0;
			displayMainMenu();
			g_getkey=KEYPAD_getPressedKey();
			LCD_clearScreen();
			LCD_displayCharacter(g_getkey);
			_delay_ms(500);
			if(g_getkey ==  '-' ||  g_getkey == '+')
			{
				g_state=ENTER_PASSWORD;
			}
			else g_state=MAIN_MENU;
		}

		break;
      /*
       * state for the user to enter the password and confirm it
       */
		case ENTER_PASSWORD:{
			displayEnterPassword();
			getPassword(g_password);
			MCSendState(CONFIRM_PASSWORD);
			sendPassword(g_password);
			_delay_ms(500);
			uint8 state= MCReceiveState();
			if(state == MATCHED){

				if(g_getkey =='+')
				{
					openDoor();
					g_state=MAIN_MENU;
				}
				else
					g_state=CREATE_PASSWORD;
			}
			else if(state == NOT_MATCHED)
			{
				displayNotMatched();
				g_error++;
				if(g_error==MAX_ERROR) {
					g_error=0;
					maxErrorOcurred();
					g_state= MAIN_MENU;
				}
				else g_state=ENTER_PASSWORD;

			}
			break;

		}

		}
	}

}

/*
 * display on lcd enter password
 */
void displayEnterPassword(){
	LCD_clearScreen();
	LCD_displayString("plz enter pass:");
	LCD_moveCursor(1, 0);
}
/*
 * display on lcd re_enter password
 */
void displayRe_EnterPassword(){
	LCD_clearScreen();
	LCD_displayString("plz re-enter the");
	LCD_moveCursor(1, 0);
	LCD_displayString("same pass:");
}
/*
 * Function to check if the other MC is ready to recieve the bytes from this MC
 */
void MCSendState(uint8 MC_state){
	UART_sendByte(MC_READY);
	while(UART_recieveByte()!= MC_READY);
	UART_sendByte(MC_state);
	while(UART_recieveByte()!=DONE);
}

/*
 * function used to display on the lcd the mainmenu options
 */
void displayMainMenu(){
	LCD_clearScreen();
	LCD_displayString(" + : Open Door");
	LCD_moveCursor(1, 0);
	LCD_displayString(" - : Change Pass ");
}
/*
 * Function to confirm that the MC is ready to recieve the bytes from other MC
 */
uint8 MCReceiveState(void){
	while(UART_recieveByte() != MC_READY){};
	UART_sendByte(MC_READY);
	uint8 state=UART_recieveByte();
	UART_sendByte(DONE);
	return state;
}

/*
 * function to get the password from user from keypad and save to the array
 */
void getPassword(uint8 arr[]){
	uint8 i=0;
	uint8 g_key_pressed=KEYPAD_getPressedKey();
	_delay_ms(600);
	while(g_key_pressed!='='){

		if(g_key_pressed>=0&&g_key_pressed<=9){
			if(i<PASSWORD_SIZE){
				arr[i]=g_key_pressed;
				LCD_displayCharacter('*');
				i++;
			}
		}
		g_key_pressed=KEYPAD_getPressedKey();
		_delay_ms(600);
	}
}

/*
 * Function to display error on lcd for 1 min if number of trials exceed max errors
 */
void maxErrorOcurred(){
	MCSendState(BUZZER_ON);
	LCD_clearScreen();
	LCD_displayString("ERROR");
	timer1_delay(60);
	LCD_clearScreen();
}

/*
 * display on the screen that the password is incorrect
 */
void displayNotMatched(){
	LCD_clearScreen();
	LCD_displayString("wrong pass");
	_delay_ms(1000);
}

/*
 * function to send the saved password to the another MC using Uart
 */
void sendPassword(uint8 send_pass[5]){
	int i=0;
	while(i < PASSWORD_SIZE){
		UART_sendByte(send_pass[i]);
		i++;
		_delay_ms(20);

	}
}

/*
 * Function to control the door state with delays (locking , unlocking ,waiting)
 */

void openDoor(){

	MCSendState(OPEN_DOOR);

	LCD_clearScreen();
	LCD_displayString("Door Unlocking");

	timer1_delay(15);
	LCD_clearScreen();
	LCD_displayString("waiting");

	timer1_delay(3);
	LCD_clearScreen();
	LCD_displayString("Door is locking");

	timer1_delay(15);
	LCD_clearScreen();
	g_state=MAIN_MENU;

}
/*
 * function to calculate any delay using timer 1
 */

void timer1_delay(int num){
	g_tick=0;
	Timer1_setCallBack(timer_callBack);
	Timer1_ConfigType  config_ptr;
	config_ptr.initial_value=0;
	config_ptr.compare_value=8000;
	config_ptr.mode=COMPARE_MODE;
	config_ptr.prescaler=F_CPU_1024;
	Timer1_init(&config_ptr);
	while(g_tick<num);
	Timer1_deInit();
}

/*
 * call back function for the timer 1 calculate g_tick++
 */
void timer_callBack(){
	g_tick++;
}



