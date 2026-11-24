# STM32 from reset

A bare-metal STM32 project for learning how bootloaders work, from reset to handing off to an app. Tested on a NUCLEO-G474RE (forgot where I put my NUCLEO-G431RB).

On reset, the bootloader lights LD2 once and leaves it off briefly. Then the app blinks LD2 rapidly.
