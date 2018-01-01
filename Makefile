#
# Project name
TARG=test_fw
F_CPU = 11059200

CC = avr-gcc
OBJCOPY = avr-objcopy
DASM = avr-objdump
SIZE = avr-size

FLASHTOOL = avrdude
FLASHDEV = usbasp
FLASHPORT = /dev/ttyUSB0

SRCS =  

OBJS = $(SRCS:.c=.o)

MCU=attiny45
# Compiler flags, F_CPU define MCU frequency
CFLAGS +=  -std=c99 -mmcu=$(MCU) -Wall -g -Os -Werror -lm  -mcall-prologues  -DF_CPU=$(F_CPU)  -Wl,-u,vfprintf -lprintf_flt
#CFLAGS = -mmcu=$(MCU) -Wall -g -Os  -lm  -mcall-prologues  -DF_CPU=$(F_CPU) -DDEBUG -Wl,-u,vfprintf -lprintf_flt
LDFLAGS = -mmcu=$(MCU)  -Wall -g -Os  -Werror -Wl,-u,vfprintf

all: $(TARG)

$(TARG): $(OBJS)
	$(CC) $(LDFLAGS) -o $@.elf  $(OBJS) -lm
	$(OBJCOPY) -O binary -R .eeprom -R .nwram  $@.elf $@.bin
	$(OBJCOPY) -O ihex -R .eeprom -R .nwram  $@.elf $@.hex
	$(DASM) -d $@.elf > $@.asm
	$(SIZE)  $@.elf > size.lst
	cat size.lst

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf *.elf *.bin *.hex $(OBJS) *.map size.lst $(TARG).asm sources.tgz

reflash: $(TARG) 	
	$(FLASHTOOL) -p $(MCU) -c $(FLASHDEV) -P $(FLASHPORT) -U flash:w:$(TARG).hex:i

sources.tgz: $(wildcard *.c) $(wildcard *.h) $(wildcard tests/*.c) $(wildcard tests/*.h) Makefile tests/Makefile README.md
	tar zcvf sources.tgz $^

