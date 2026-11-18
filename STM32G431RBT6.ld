/* STM32G431RBT6 */

MEMORY
  {
    /*
     * STM32G431RBT6 DATASHEET (DS12589 Rev 6)
     * https://www.st.com/resource/en/datasheet/stm32g431rb.pdf
     *
     * Table 2 (p. 14) shows the STM32G431RBT6 has 128KB of
     * flash memory and 32KB of SRAM.
     *
     * Section 3.5 (Embedded SRAM, p. 18) describes SRAM1, SRAM2,
     * and the CCM alias, together providing 32KB of contiguous SRAM
     * from 0x2000 0000 to 0x2000 7FFF.
     * 
     * STM32G4 SERIES REFERENCE MANUAL (RM0440)
     * https://www.st.com/resource/en/reference_manual/rm0440-stm32g4-series-advanced-armbased-32bit-mcus-stmicroelectronics.pdf
     *
     * Section 5.3.1 (p. 189) shows the 128KB address layout as from
     * 0x0800 0000 to 0x0801 FFFF.
     */

    flash (rx)  : ORIGIN = 0x08000000, LENGTH = 128K
    sram  (rwx) : ORIGIN = 0x20000000, LENGTH = 32K
  }
