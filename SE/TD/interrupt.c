#include "interrupt.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "ring_buffer.h"

void initInterrupt() {
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);   // Turn on the transmission and reception circuitry
    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01); // Use 8-bit character sizes

    UBRR0H = MYUBRR >> 8; // Load upper 8-bits of the baud rate value into the high byte of the UBRR register
    UBRR0L = MYUBRR; // Load lower 8-bits of the baud rate value into the low byte of the UBRR register

    UCSR0B |= (1 << RXCIE0); // Enable the USART Recieve Complete interrupt (USART_RXC)

    sei(); // Enable the Global Interrupt Enable flag so that interrupts can be processed
}

ISR (USART_RX_vect) {
    char receivedByte;
    receivedByte = UDR0; // Fetch the received byte value into the variable "ByteReceived"
    ringBufferWrite(&rxRb, receivedByte);
}

ISR(USART_UDRE_vect) {
    if (!ringBufferAvailable(&txRb)) {
        UCSR0B &= ~(1 << UDRIE0);
    } else {
        UDR0 = ringBufferRead(&txRb);
    }
}
