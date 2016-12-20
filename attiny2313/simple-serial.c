// this is the header file that tells the compiler what pins and ports, etc.
// are available on this chip.
#include <avr/io.h>
#include <util/delay.h>

// Some macros that make the code more readable
#define output_low(port,pin) port &= ~(1<<pin)
#define output_high(port,pin) port |= (1<<pin)
#define set_input(portdir,pin) portdir &= ~(1<<pin)
#define set_output(portdir,pin) portdir |= (1<<pin)

void USART_Transmit( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )
	{ }
	/* Put data into buffer, sends the data */
	UDR = data;
}

void init_USART( uint16_t baud_rate )
{
	/* Set double USART speed */
	UCSRA = (1<<U2X);
	/* Set baud rate */
	UBRRH = (unsigned char)(baud_rate>>8);
	UBRRL = (unsigned char)baud_rate;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<TXEN);
	/* Default frame format: 8data, no parity bit, 1stop bit */
}

int main(void) 
{
	init_USART(12); //Set baud rate to 9600 (pg 136 table 57 of datasheet)

	while (1) 
	{
		uint16_t time = 1000;
	  
		USART_Transmit('H');
		USART_Transmit('e');
		USART_Transmit('l');
		USART_Transmit('l');
		USART_Transmit('o');
		USART_Transmit(' ');
		USART_Transmit('W');
		USART_Transmit('o');
		USART_Transmit('r');
		USART_Transmit('l');
		USART_Transmit('d');
		USART_Transmit('!');
		USART_Transmit((char)13); //Carriage Return
		USART_Transmit((char)10); //Line Feed
		_delay_ms(time);
		// now start over
	}
}