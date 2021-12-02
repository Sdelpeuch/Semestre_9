#include <avr/io.h>
#include <util/delay.h>

/*
 * Blink a LED on pin PB5
 */
void blink(){
    DDRD |= _BV(PD6);
    for (int i = 0; i < 300; ++i) {
        PORTD |= _BV(PD6);
        _delay_ms(200);
        PORTD &= ~_BV(PD6);
        _delay_ms(200);
    }
}