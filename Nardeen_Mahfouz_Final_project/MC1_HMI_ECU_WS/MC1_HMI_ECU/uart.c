/*
 * uart.c
 * Author: Nardeen
 */

#include "uart.h"
#include "common_macros.h"
#include <avr/io.h>

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */

void UART_init(const UART_ConfigType * Config_Ptr){

	UCSRA =(1<<U2X);
	UCSRB =(1<<RXEN)|(1<<TXEN);
	UCSRC = (1<<URSEL) | (Config_Ptr->bit_data << 1)  | (Config_Ptr->stop_bit << 3)|(Config_Ptr->parity << 4);
	uint16 ubrr_value = (uint16)(((F_CPU / (Config_Ptr->baud_rate * 8UL))) - 1);
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
}
/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */

void UART_sendByte(const uint8 data){

while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	UDR = data;

}
/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(){
	while(BIT_IS_CLEAR(UCSRA,RXC)){}
	    return UDR;
}
/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str){
	while(*Str != '\0')
		{
			UART_sendByte(*Str);
			Str++;
		}

}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */

void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	Str[i] = UART_recieveByte();

	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	Str[i] = '\0';
}

