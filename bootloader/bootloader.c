#include "bootloader.h"

#include "memory_map.h"

#include <stdint.h>

static void start_app(uint32_t pc, uint32_t sp) {
  __asm("\n\
      msr msp, r1\n\
      bx r0\n\
      ");
}

int bootloader_main(void) {
  const uint32_t *app_code = &__approm_start__;
  uint32_t app_sp = app_code[0];
  uint32_t app_start = app_code[1];
  start_app(app_start, app_sp);

  while (1);
}
