#include "app.h"
#include <stdint.h>

#define RCC_BASE 0x40021000U
#define AHB2ENR_OFFSET 0x4CU

#define GPIOA_BASE 0x48000000U
#define GPIOx_MODER 0x00U
#define GPIOA_ODR_OFFSET 0x14U

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

  for (int i = 0; i < 67000; ++i) {};
}

void app_main(void) {
  gpioa_init();
  while (1) {
    pa5_toggle();
  }
  gpioa_deinit();
}
