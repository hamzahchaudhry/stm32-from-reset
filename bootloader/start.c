#include "bootloader.h"

#include <stdint.h>

extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _end;

void Reset_Handler(void);

__attribute__((section(".vector")))
static const uintptr_t vector_table[] = {
  (uintptr_t)&_end, // MSP
  (uintptr_t)Reset_Handler
};

void Reset_Handler(void) {
  // vector table address? idk if it should be here
  volatile uint32_t *vtor = (volatile uint32_t *)0xE000ED08;

  // RM0440 Rev 9 Section 14.3 lists 102 IRQs. Adding the 16
  // system reserved exceptions gives us a total of 118 entries
  // in the table. So, the vector table must be:
  // 118 * 4 = 472, with the next power of 2 being 512, so it
  // must be 512-byte aligned.
  // *vtor = ((uint32_t)(uintptr_t)vector_table & 0xFFFFFFE0);
  *vtor = (uint32_t)(uintptr_t)vector_table;

  // initialize BSS to 0
  uint32_t *pbss = &_sbss;
  while (pbss != &_ebss) {
    *pbss++ = 0;
  }

  // copy initial values
  uint32_t *pinit = &_etext;
  uint32_t *pdata = &_sdata;
  while (pdata != &_edata) {
    *pdata++ = *pinit++;
  }

  // enter application code
  bootloader_main();

  // protect against main returning
  while (1);
}
