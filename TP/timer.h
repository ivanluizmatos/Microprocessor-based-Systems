#ifndef TIMER
#define TIMER

#include "stm32l475xx.h"
#include "led.h"
#include "trames.h"

extern volatile uint8_t trame[192];

void timer_init(int max_us);

#endif