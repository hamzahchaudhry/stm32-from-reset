PROJECT = raw
BUILD_DIR = build

OCPY = arm-none-eabi-objcopy

.PHONY: all $(PROJECT).bin clean

all: $(PROJECT).bin

$(BUILD_DIR)/bootloader-padded.bin: bootloader/build/bootloader.elf
	mkdir -p $(@D)
	$(OCPY) -O binary --pad-to=0x08007000 --gap-fill=0xFF $< $@

$(PROJECT).bin: $(BUILD_DIR)/$(PROJECT).bin
$(BUILD_DIR)/$(PROJECT).bin: $(BUILD_DIR)/bootloader-padded.bin app/build/app.bin
	cat $^ > $@

clean:
	rm -rf $(BUILD_DIR)
