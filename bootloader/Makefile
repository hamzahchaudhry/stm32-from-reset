CC = arm-none-eabi-gcc 
CPU = -mcpu=cortex-m4
MCU = $(CPU) -mthumb

CFLAGS = -ffreestanding -Og -Wall -Wextra -Wpedantic
 
LDSCRIPT = STM32G431RBT6.ld
LDFLAGS = -nostdlib -T$(LDSCRIPT)

.PHONY: all bootloader.elf bootloader.bin clean

all: bootloader.elf bootloader.bin

bootloader.elf: build/bootloader.elf
build/bootloader.elf: bootloader.c start.c $(LDSCRIPT) Makefile
	mkdir -p $(@D)
	$(CC) $(MCU) $(CFLAGS) $(LDFLAGS) $(filter %.c,$^) -o $@

bootloader.bin: build/bootloader.bin
build/bootloader.bin: build/bootloader.elf
	mkdir -p $(@D)
	arm-none-eabi-objcopy -O binary $< $@

clean:
	rm -rf build
