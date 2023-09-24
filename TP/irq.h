#ifndef IRQ
#define IRQ

#include <stdint.h>
#include "stm32l475xx.h"

extern char _stack_start, _start;

void irq_init();

#endif