#include "uart.h"
#include <stdio.h>
#include "interrupt.h"
#include "ring_buffer.h"

int main() {
    uartInit(MYUBRR);
    initInterrupt();
    ringBufferInit(&txRb);
    ringBufferInit(&rxRb);
    while (1) {
        if (uartAvailable()) {
            unsigned char c = uartReceive();
            char buffer[32];
            if (c == 13) {
                sprintf(buffer, "\r\n");
            } else if (c == 127) {
                sprintf(buffer, "\b");
            } else {
                sprintf(buffer, "%c", c);
            }
            uartTransmitString(buffer);
        }
    }
}

