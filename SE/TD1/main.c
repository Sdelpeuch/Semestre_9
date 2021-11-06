#include <avr/io.h>
#include <util/delay.h>

void blink(){
    DDRB |= _BV(PB5);
    for (int i = 0; i < 300; ++i) {
        PORTB |= _BV(PB5);
        _delay_ms(200);
        PORTB &= ~_BV(PB5);
        _delay_ms(200);
    }
}

void button(){
    DDRB |= _BV(PB5);
    DDRD |= _BV(PD2);
    if(PIND & _BV(PD2)){
        PORTB |= _BV(PB5);
    }
}

int main() {
    button();
}

