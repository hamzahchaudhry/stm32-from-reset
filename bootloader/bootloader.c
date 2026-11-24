#include "bootloader.h"

#include "memory_map.h"

#include <stdint.h>

#define RCC_BASE 0x40021000U
#define AHB2ENR_OFFSET 0x4CU

#define GPIOA_BASE 0x48000000U
#define GPIOx_MODER 0x00U
#define GPIOA_ODR_OFFSET 0x14U

static void start_app(uint32_t pc, uint32_t sp) {
  (void)pc;
  (void)sp;
  __asm("\n\
      msr msp, r1\n\
      bx r0\n\
      ");
}

void gpioa_init(void) {
  // enable GPIOA clock
  // bit 0 for GPIOEN: 1=enabled
  volatile uint32_t *const ahb2enr = (volatile uint32_t *)(RCC_BASE + AHB2ENR_OFFSET);
  *ahb2enr |= 1U;

  // PA5 for on board LED
  // MODE5[1:0] = GPIOA_MODER[11:10]. we need to set this to 01.

  // set GPIO mode to output mode
  volatile uint32_t *const gpioa_moder = (volatile uint32_t *)(GPIOA_BASE + GPIOx_MODER);
  *gpioa_moder &= ~(1U << 11U);
  *gpioa_moder |= 1U << 10U;

  // i think the reset values/defaults for everything else are fine
}

void gpioa_deinit(void) {
  volatile uint32_t *const gpioa_moder = (volatile uint32_t *)(GPIOA_BASE + GPIOx_MODER);
  *gpioa_moder |= 1U << 11U;
  *gpioa_moder |= 1U << 10U;

  volatile uint32_t *const ahb2enr = (volatile uint32_t *)(RCC_BASE + AHB2ENR_OFFSET);
  *ahb2enr &= ~(1U);
}

void pa5_toggle(void) {
  volatile uint32_t *const odr = (volatile uint32_t *)(GPIOA_BASE + GPIOA_ODR_OFFSET);
  // bit 5 for pa5
  *odr ^= (1U << 5);

  for (int i = 0; i < 6259529; ++i) {};
}

int bootloader_main(void) {
  gpioa_init();

  pa5_toggle();

  const uint32_t *app_code = &__approm_start__;
  uint32_t app_sp = app_code[0];
  uint32_t app_start = app_code[1];

  pa5_toggle();

  // deinitialize hw resources so we don't break assumptions
  // app makes about state of the system
  gpioa_deinit();

  start_app(app_start, app_sp);

  while (1);
}
