#ifndef TD_UART_H
#define TD_UART_H

#define FOSC 16000000 // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

extern struct RingBuffer txRb;
extern struct RingBuffer rxRb;

void uartInit(unsigned int ubrr);
void uartTransmit(unsigned char data);
void uartTransmitString(unsigned char *data);
unsigned char uartReceive();
int uartAvailable();

#endif //TD_UART_H
