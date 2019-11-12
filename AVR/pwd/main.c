#include <avr/io.h>
#include <util/delay.h>
int main (void)
{

	DDRB  |=  (0 << PB0) | (1 << PB1) | (1 << PB2);

	OCR1A	= 0x01FF;						// set PWM for 50% duty cycle at 10bit
	TCCR1A |= (1 << COM1A1);				// set non-inverting mode
	TCCR1A |= (1 << WGM11 ) | (1 << WGM10); // set 10bit phase corrected PWM Mode
	TCCR1B |= (1 << CS11  );				// set prescaler to 8 and starts PWM

	while (1)
	{
		
		if(!(PINB & (1 << PB0)))	PORTB |=  (1 << PB2);
		else						PORTB &= ~(1 << PB2);

		_delay_ms(1000);
	}
} 
