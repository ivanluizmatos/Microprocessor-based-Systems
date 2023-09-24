#ifndef TRAMES
#define TRAMES

#include <stdint.h>
#include "stm32l475xx.h"
#include "uart.h"
#include "matrix.h"

extern volatile uint8_t trame[192];

void afficher_image_statique(volatile uint8_t image[192]);
void usart_interrupt_enable();

#endif
