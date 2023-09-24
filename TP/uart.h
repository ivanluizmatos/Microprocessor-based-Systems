#ifndef UART
#define UART

#include <stdint.h>
#include <stddef.h>
#include "stm32l475xx.h"


void uart_init(int baudrate);
void uart_putchar(uint8_t c);
uint8_t uart_getchar();
void uart_puts(const char *s);
void uart_gets(char *s, size_t size);

int bytes_sum();

#endif
