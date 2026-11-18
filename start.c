#include <stdint.h>

extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;

int main(void);

void Reset_Handler(void) {
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
  main();

  // protect against main returning
  while (1);
}

int main(void) {
  while (1);
}
