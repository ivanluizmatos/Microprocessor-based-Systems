#ifndef MATRIX
#define MATRIX

#include <stdint.h>
#include <stddef.h>
#include "stm32l475xx.h"

extern uint8_t _binary_image_raw_start; 

typedef struct {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} rgb_color;


void RST(char x);
void SB(char x);;
void LAT(char x);
void SCK(char x);
void SDA(char x);
void ROW0(char x);
void ROW1(char x);
void ROW2(char x);
void ROW3(char x);
void ROW4(char x);
void ROW5(char x);
void ROW6(char x);
void ROW7(char x);

void deactivate_rows();
void activate_row(int row);

void send_byte(uint8_t val, int bank);
void mat_set_row(int row, const rgb_color *val);

void init_bank0();

void matrix_init();

void test_pixels();

void test_image_statique();

#endif
