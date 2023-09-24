#include "led.h"
#include "stm32l475xx.h"

void led_init() {

    // Activation de l'horloge du port B (cf. page 252 du manuel de référence)
    // AVANT: RCC_AHB2ENR |= (0b1 << 1);
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

    // Configuration de la broche PB14 en mode sortie (cf. page 303)
    // AVANT: GPIOB_MODER = ( GPIOB_MODER & ~(0x3 << 28) ) | (0x1 << 28);
    GPIOB->MODER = ( GPIOB->MODER & ~(0x3 << GPIO_MODER_MODE14_Pos) ) | (0x1 << GPIO_MODER_MODE14_Pos);

    // Activation de l'horloge du port C (cf. page 252)
    // AVANT: RCC_AHB2ENR |= (0b1 << 2);
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
   
}

void led_g_on() {    // cf. page 306
    // Pour allumer la LED2 (verte), il faut mettre la broche PB14 à l'état haut. 
    // Cette fonction écrit 1 dans le bit 14 (BS14) et 0 dans le bit 30 (BR14) 
    // du registre GPIOB_BSRR
    // AVANT: GPIOB_BSRR |=  (0x1 << 14);
    // AVANT: GPIOB_BSRR &= ~(0x1 << 30);
    GPIOB->BSRR = GPIO_BSRR_BS14;
}

void led_g_off() {    // cf. page 306
    // Pour éteindre la LED2 (verte), il faut mettre la broche PB14 à l'état bas. 
    // Cette fonction écrit 1 dans le bit 30 (BR14) et 0 dans le bit 14 (BS14) 
    // du registre GPIOB_BSRR
    // AVANT: GPIOB_BSRR |=  (0x1 << 30);
    // AVANT: GPIOB_BSRR &= ~(0x1 << 14);
    GPIOB->BSRR = GPIO_BSRR_BR14;
}


void led(state led_state) {
    
    if (led_state == LED_OFF) {
        // Configuration de la broche PC9 en mode entrée (haute impédance) (cf. page 303)
        // AVANT: GPIOC_MODER = GPIOC_MODER & ~(0x3 << 18);
        GPIOC->MODER = GPIOC->MODER & ~(0x3 << GPIO_MODER_MODE9_Pos);
    }

    else {

        // Configuration de la broche PC9 en mode sortie (cf. page 303)
        // AVANT: GPIOC_MODER = ( GPIOC_MODER & ~(0x3 << 18) ) | (0x1 << 18);
        GPIOC->MODER = ( GPIOC->MODER & ~(0x3 << GPIO_MODER_MODE9_Pos) ) | (0x1 << GPIO_MODER_MODE9_Pos);
        
        if (led_state == LED_YELLOW) {
        // Quand PC9 est à l'état haut (1), la LED3 (jaune) est allumé et la LED4 (bleue) est éteinte.
        // Donc, pour allumer la LED3 (jaune), on écrit 1 dans le bit 9 (BS9) et 0 dans le bit 25 (BR9)
        // du registre GPIOC_BSRR (cf. page 306).
            // AVANT: GPIOC_BSRR |=  (0x1 << 9);
            // AVANT: GPIOC_BSRR &= ~(0x1 << 25);
            GPIOC->BSRR = GPIO_BSRR_BS9;
        }

        else if (led_state == LED_BLUE) {
        // Quand PC9 est à l'état bas (0), la LED4 (bleue) est allumé et la LED3 (jaune) est éteinte.
        // Donc, pour allumer la LED4 (bleue), on écrit 1 dans le bit 25 (BR9) et 0 dans le bit 9 (BS9)
        // du registre GPIOC_BSRR (cf. page 306).
            // AVANT: GPIOC_BSRR |=  (0x1 << 25);
            // AVANT: GPIOC_BSRR &= ~(0x1 << 9);
            GPIOC->BSRR = GPIO_BSRR_BR9;
        }

    }

}
