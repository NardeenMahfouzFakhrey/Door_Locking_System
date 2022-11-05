/*
 * MC1.c
 *
 *  Created on: 30 Oct 2022
 *      Author: EES
 */

#include "MC2.h"


int main(){

	SREG |= (1<<7); //enable global interrupts
	UART_init(&uart_Config_Ptr); //initialize uart
	DcMotor_Init(); // initialize Dc motor

	while(1) {

		switch (MCReceiveState()){
		/*
		 * case for Mc to Recieve password from other MC
		 */
		case SEND_PASSWORD:
		{
			recievePassword();
			saveInMemory();
		}

		break;
		/*
		 * case for check if the password is correct
		 */

		case CONFIRM_PASSWORD:

		{
			recievePassword();
			readFromMemory();
			checkPassword();
		}
		break;
		/*
		 *  case for turning on the buzzer in case of error
		 */
		case BUZZER_ON:
		{
			Buzzer_on();
			timer1_delay(60);
			Buzzer_off();
		}
		break;
		/*
		 * case for openning door to control Dc motor with delays
		 */
		case OPEN_DOOR:
		{
			DcMotor_Rotate(CLOCKWISE, 100);
			timer1_delay(15);
			DcMotor_Rotate(STOP, 100);
			timer1_delay(3);
			DcMotor_Rotate(ANTI_CLOCKWISE, 100);
			timer1_delay(15);
			DcMotor_Rotate(STOP, 100);
		}
		break;
		}

	}
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
 * Function to check if the other MC is ready to recieve the bytes from this MC
 */
void MCSendState(uint8 state){
	UART_sendByte(MC_READY);
	while(UART_recieveByte()!=MC_READY);
	UART_sendByte(state);
	while(UART_recieveByte()!=DONE);
}
/*
 * function to recieve password from another Mc using uart
 */
void recievePassword(){
	int i=0;
	while(i < PASSWORD_SIZE){
		g_password[i]= UART_recieveByte();
		i++;
	}
}
/*
 * function to save password in memory
 */
void saveInMemory(){
	int i=0;
	while(i < PASSWORD_SIZE){
		EEPROM_writeByte(EEPROM_ADDRRESS +i ,g_password[i] );
		i++;
		_delay_ms(10);
	}
}
/*
 * Function to read password from memory
 */
void readFromMemory(){
	int i=0;
	while(i < PASSWORD_SIZE){
		EEPROM_readByte( EEPROM_ADDRRESS +i ,&g_eeprom_password[i] );
		i++;
		_delay_ms(10);}
}
/*
 * function check if the password is correct
 */
void checkPassword(){
	int i=0,flag=0;
	while(i < PASSWORD_SIZE) {
		if(g_eeprom_password[i] != g_password[i]){
			flag=1;
			break;
		}
		i++;
	}

	if(flag==1){
		MCSendState(NOT_MATCHED);
	}
	else MCSendState(MATCHED);

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
