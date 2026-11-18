CC = arm-none-eabi-gcc 
CPU = -mcpu=cortex-m4
MCU = $(CPU) -mthumb

CFLAGS = -ffreestanding -Og -Wall -Wextra -Wpedantic
 
LDSCRIPT = STM32G431RBT6.ld
LDFLAGS = -nostdlib -T$(LDSCRIPT)

.PHONY: all firmware.elf firmware.bin clean

all: firmware.elf firmware.bin

firmware.elf: build/firmware.elf
build/firmware.elf: start.c $(LDSCRIPT) Makefile
	mkdir -p $(@D)
	$(CC) $(MCU) $(CFLAGS) $(LDFLAGS) $< -o $@

firmware.bin: build/firmware.bin
build/firmware.bin: build/firmware.elf
	mkdir -p $(@D)
	arm-none-eabi-objcopy -O binary $< $@

clean:
	rm -rf build
