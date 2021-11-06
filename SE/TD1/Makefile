CC=avr-gcc
OBJCOPY=avr-objcopy
PLATFORM = atmega328p
CFLAGS=-Os -DF_CPU=16000000UL -mmcu=$(PLATFORM)
PORT=/dev/ttyACM0
OBJECTS = main

all: main.hex

main.hex: main.elf
	$(OBJCOPY) -O ihex -R .eeprom main.elf main.hex

main.elf: $(OBJECTS).o
	$(CC) -o $@ $^ $(CFLAGS)

install: main.hex
	avrdude -F -V -c arduino -p $(PLATFORM) -P $(PORT) -b 115200 -U flash:w:main.hex:i

clean:
	rm -f *.elf *.hex *.o