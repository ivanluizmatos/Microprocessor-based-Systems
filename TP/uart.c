#include "uart.h"

#define CLK_FREQ 80000000

int sum = 0;

void uart_init(int baudrate) {

    // Activation de l'horloge du port B (cf. page 252 du manuel de référence)
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    // Configuration de la broche PB6 en mode "Alternate Function" (cf. page 303)
    GPIOB->MODER = ( GPIOB->MODER & ~(0x3 << GPIO_MODER_MODE6_Pos) ) | (0b10 << GPIO_MODER_MODE6_Pos);
    
    // Configuration de la broche PB6 comme USART1_TX (cf. page 307 du manuel et page 70 du datasheet)
    GPIOB->AFR[0]  = ( GPIOB->AFR[0] & ~(0xF << GPIO_AFRL_AFSEL6_Pos) ) | (0b0111 << GPIO_AFRL_AFSEL6_Pos);

    // Configuration de la broche PB7 en mode "Alternate Function" (cf. page 303)
    GPIOB->MODER = ( GPIOB->MODER & ~(0x3 << GPIO_MODER_MODE7_Pos) ) | (0b10 << GPIO_MODER_MODE7_Pos);

    // Configuration de la broche PB7 comme USART1_RX (cf. page 307 du manuel et page 70 du datasheet)
    GPIOB->AFR[0]  = ( GPIOB->AFR[0] & ~(0xF << GPIO_AFRL_AFSEL7_Pos) ) | (0b0111 << GPIO_AFRL_AFSEL7_Pos);

    // Activation de l'horloge du port série USART1 (cf. pages 258 et 259 du manuel)
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    
    // Spécifier que l'horloge pour l'USART1 est PCLK
    RCC->CCIPR &= ~RCC_CCIPR_USART1SEL;

    // Reset du port série USART1
    RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
    RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;

    // Configuration de la vitesse du port série (cf. pages 1349 et 1388 du manuel)
    // USART1->BRR = ( USART1->BRR & (~0xF) ) | ( (uint32_t)(CLK_FREQ/BAUD_RATE) & 0xF );
    USART1->BRR = CLK_FREQ/baudrate;

    // Configuration de l'oversampling à 16 (cf. page 1377 et 1378 du manuel)
    USART1->CR1 &= ~USART_CR1_OVER8;

    // Configuration de la port série en mode 8N1 (cf. pages 1376-1383)
    USART1->CR1 &= ~(USART_CR1_M1 | USART_CR1_M0); // pour avoir 8 bits de données (cf. pages 1376, 1377)
    USART1->CR1 &= ~USART_CR1_PCE;                 // pour n'avoir pas de parité (cf. page 1377)
    USART1->CR2 &= ~(USART_CR2_STOP);              // pour qu'il y aie seulement 1 bit de stop

    // Activation de l'USART1, du transmetteur et du récepteur (cf. pages 1378, 1379)
    USART1->CR1 |= (USART_CR1_UE | USART_CR1_TE | USART_CR1_RE);

}


void uart_putchar(uint8_t c) {

    while ( !(USART1->ISR & USART_ISR_TXE) ) { }

    USART1->TDR = c;

}


uint8_t uart_getchar() {

    while ( !(USART1->ISR & USART_ISR_RXNE) ) { 
        
        // Vérification d'erreur de framing ou overrun
        if ( USART1->ISR & (USART_ISR_FE | USART_ISR_ORE) ) {
            while(1) {} // S'il y a eu une erreur de framing ou d'overrun, déclenche une boucle infinie
        }  
   
    }

    return ( (uint8_t) (USART1->RDR & USART_RDR_RDR_Msk) );

}


void uart_puts(const char *s) {

    while (*s != 0) {
        uart_putchar(*s);
        s++;
    }
    uart_putchar('\n'); uart_putchar('\r');

}


void uart_gets(char *s, size_t size) {

    for (int i = 0; i < (int) size; i++) {
        *s = uart_getchar();
        s++;
    }
    *s = '\0';

}


int bytes_sum () {

    /*
    Cette fonction n'arretera pas automatiquement. Afin de vérifier si la somme est
    correcte, il faut arreter l'éxecution (en faisant CTRL+C), et après lire la
    valeur de la variable sum, en utilisant le commande 'display sum'.
    */

    while(1) {
        sum += (int) uart_getchar();
    }

}
