#include <avr/io.h>
#include <util/delay.h>

int main(void) {

  int count;

  DDRB |= (1 << PB5); // Set the pinb5(13) to output
  PORTB |= (1 << PB5); // set pinb5(13) on

  for (;;) {
    PORTB |= (1 << PB5);// set pinb5(13) on

    if (count > 6)
      count = 0;

    else if (count > 3)
      _delay_ms(500);

    else if (count > 0)
      _delay_ms(1000);

    PORTB &= ~(1 << PB5); // set pinb5(13) off
    _delay_ms(250);
    count++;
  }
  return 0;
}
