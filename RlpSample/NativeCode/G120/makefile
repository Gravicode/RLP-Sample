################################################
###### Copyright (c) GHI Electronics, LLC ######
################################################

OUTFILE = G120RLP
LINKERSCRIPT = LinkerScript.lds

MCU = cortex-m3
MCFLAGS = -mcpu=$(MCU)

CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc

CCFLAGS = -g -mlittle-endian $(MCFLAGS) -mthumb  -Wall -I. -mapcs-frame -fno-builtin

LDFLAGS = $(MCFLAGS) -mthumb -nostartfiles -Wl,--Map -Wl,./$(OUTFILE).map -lc -lgcc -Wl,--omagic -T $(LINKERSCRIPT)

OBJS += NativeCode.o 

rebuild: clean all del

all: $(OBJS)
	$(LD) $(LDFLAGS) -o ./$(OUTFILE).elf $(OBJS)

clean:
	-rm ./*.elf ./*.map ./*.lst

del:
	-rm ./*.o

NativeCode.o: NativeCode.c 
	$(CC) -c $(CCFLAGS) NativeCode.c -o NativeCode.o
