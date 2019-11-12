#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRB |= (1 << PB0) | (1 << PB3);
	PORTB |= (1 << PD1); // PULL-UP

	while(1) {
		if(!(PINB & (1 << PB1)))
			PORTB |=  (1 << PB0);
		else
			PORTB &= ~(1 << PB0);

		_delay_ms(1000);
	}
	
	return 0;
}
