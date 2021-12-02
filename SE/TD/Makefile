CC=avr-gcc
OBJCOPY=avr-objcopy
PLATFORM = atmega328p
CFLAGS=-Os -DF_CPU=16000000UL -mmcu=$(PLATFORM)
PORT=/dev/ttyACM0
BIN = main
OBJS=main.o uart.o interrupt.o ring_buffer.o

all: $(BIN).hex

$(BIN).hex: $(BIN).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

$(BIN).elf: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

install: ${BIN}.hex
	avrdude -F -V -c arduino -p $(PLATFORM) -P $(PORT) -b 115200 -U flash:w:$<

clean:
	rm -f ${BIN}.elf ${BIN}.hex ${OBJS}