#include <stdint.h>
#include "clocks.h"
#include "uart.h"
#include "matrix.h"

#include "led.h"
#include "irq.h"
#include "buttons.h"
#include "trames.h"

#include "timer.h"

volatile uint8_t trame[192];

int main() {

    clocks_init();

    matrix_init();

    irq_init();

    led_init();

    button_init();

    uart_init(38400);

    usart_interrupt_enable();

    timer_init(1000000/(8*60));     // Pour comprendre la choix de cette valeur du paramètre (correspondant à une "fréquence d'appel du handler"
                                    // égale à 8*60 Hz), voir l'explication présente dans les commentaires du fichier timer.c

    while(1) { }

    return 0;
}
