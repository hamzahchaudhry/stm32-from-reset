CC = arm-none-eabi-gcc 
CPU = -mcpu=cortex-m4
MCU = $(CPU) -mthumb

CFLAGS = -ffreestanding -Og -Wall -Wextra -Wpedantic
 
LDSCRIPT = STM32G431RBT6.ld
LDFLAGS = -nostdlib -T$(LDSCRIPT)

.PHONY: all app.elf app.bin clean

all: app.elf app.bin

app.elf: build/app.elf
build/app.elf: app.c start.c $(LDSCRIPT) Makefile
	mkdir -p $(@D)
	$(CC) $(MCU) $(CFLAGS) $(LDFLAGS) $(filter %.c,$^) -o $@

app.bin: build/app.bin
build/app.bin: build/app.elf
	mkdir -p $(@D)
	arm-none-eabi-objcopy -O binary $< $@

clean:
	rm -rf build
