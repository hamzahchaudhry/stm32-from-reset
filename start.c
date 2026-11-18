void Reset_Handler(void) {
  // initialize BSS to 0
  uint32_t *pbss = &_sbss;
  while (*pbss != &_ebss) {
    *pbss++ = 0;
  }

  // copy initial values
  uint32_t *pinit = &_etext;
  uint32_t *pdata = &_sdata;
  while (*pdata != &_edata) {
    *pdata++ = *pinit++;
  }

  // enter application code
  main();

  // protect against main returning
  while (1);
}
