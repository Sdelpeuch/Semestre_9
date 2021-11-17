#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>
/*
 * Blink a LED on pin PB5
 */
void blink(){
    DDRB |= _BV(PB5);
    for (int i = 0; i < 300; ++i) {
        PORTB |= _BV(PB5);
        _delay_ms(200);
        PORTB &= ~_BV(PB5);
        _delay_ms(200);
    }
}

int main() {
//    blink();
    uartInit(MYUBRR);
    while(1) {
        uartTransmitString("Hello \n");
        delay(300);
    }
    char* data = uartReceive();
}

