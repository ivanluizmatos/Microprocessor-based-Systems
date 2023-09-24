#include "buttons.h"

void button_init() {

    // Activation de l'horloge du port C (cf. page 252 du manuel)
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;

    // Configuration de la broche PC13 en mode entrée (cf. page 303)
    GPIOC->MODER &= ~GPIO_MODER_MODE13_Msk;

    // Configuration de la broche PC13 comme source d'IRQ pour EXTI13 (cf. page 403)
    SYSCFG->EXTICR[3] = (SYSCFG->EXTICR[3] & ~SYSCFG_EXTICR4_EXTI13_Msk) | SYSCFG_EXTICR4_EXTI13_PC;

    // Configuration de l'EXTI selon la procédure décrite en 14.3.4. (manuel de référence, page 402)
    EXTI->IMR1 |= EXTI_IMR1_IM13_Msk; // Configuration du bit de mask, pour activer l'interruption de la ligne 13
    EXTI->FTSR1 |= EXTI_FTSR1_FT13_Msk;   // "Falling trigger enabled" (cf. page 406)
    EXTI->RTSR1 &= ~EXTI_RTSR1_RT13_Msk;  // "Rising trigger disabled" (cf. page 406)
    NVIC_EnableIRQ(40); // Activation des interruptions provenantes des lignes de l'EXTI (cf. page 397)
 
}

void EXTI15_10_IRQHandler() {

    // Acquittement de l'interruption dans l'EXTI
    EXTI->PR1 |= EXTI_PR1_PIF13_Msk;

    // Pour effectuer le "toggle" du LED verte (broche PB14), on lit la valeur actuelle de la 
    // broche PB14, et après on lui attribue la valeur contraire (afin de changer l'état de la LED). 
    // Les lignes de code suivantes servent à "toggler" la LED verte :    

    int current_state = GPIOB->ODR & GPIO_ODR_OD14_Msk; // Lecture du état actuel de la broche PB14 (LED verte)
    
    if (current_state)
        led_g_off();    // Pour éteindre la LED verte si elle est allumée
    else
        led_g_on();     // Pour allumer la LED verte si elle est éteinte

    // Remarque : les fonctions led_g_off et led_g_on ont été définies dans le fichier led.c,
    // pour cette raison, dans le fichier buttons.h, on fait : #include "led.h".

}
