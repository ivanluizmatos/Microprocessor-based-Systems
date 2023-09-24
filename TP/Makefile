PREFIX=arm-none-eabi-
AS    = $(PREFIX)as
LD    = $(PREFIX)ld

CC = $(PREFIX)gcc

GDB   = $(PREFIX)gdb

OBJCOPY = $(PREFIX)objcopy

ASFLAGS = -g
LDFLAGS = -T ld_ram.lds -nostdlib

NEWDIR = -I CMSIS/Device/ST/STM32L4xx/Include -I CMSIS/Include

CFLAGS = -c -g -Og -Wall -Wextra -Werror -ffreestanding $(NEWDIR)
TARGET_ARCH = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16
TARGET_MACH = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16

ELFFILES = main

OBJS = main.o crt0.o init.o memfuncs.o led.o uart.o matrix.o image.o irq.o buttons.o trames.o timer.o clocks.o

all: $(ELFFILES)

$(ELFFILES): $(OBJS)

image.o : image.raw
	$(OBJCOPY) -I binary -O elf32-littlearm -B arm image.raw image.o

.PHONY: connect debug clean all

connect:
	stty -F /dev/ttyACM0 38400 raw -echo -echoe -echok -crtscts clocal
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug:
	$(GDB) -x se203.gdb

clean:
	rm -f $(ELFFILES)
	rm -f $(OBJS)
