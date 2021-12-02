
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "ring_buffer.h"

struct RingBuffer txRb;
struct RingBuffer rxRb;

void uartInit(unsigned int ubrr) {
    UBRR0H = (unsigned char) (ubrr >> 8);
    UBRR0L = (unsigned char) ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);
}

void uartTransmit(unsigned char data) {
    ringBufferWrite(&txRb, data);
    UCSR0B |= (1 << UDRIE0);
}

void uartTransmitString(unsigned char* data) {
    while (*data != 0) {
        uartTransmit(*data);
        data++;
    }
}


int uartAvailable(){
    return ringBufferAvailable(&rxRb);
}

unsigned char uartReceive() {
    return ringBufferRead(&rxRb);
}