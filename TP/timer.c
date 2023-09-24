#include "timer.h"

void timer_init(int max_us) {

    // Activation de l'horloge du timer TIM2
    RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;

    // Effacement des flags dans le registre de statut et mise à zero de la valeur du compteur
    TIM2->SR  &= ~( TIM_SR_CC4OF_Msk | TIM_SR_CC3OF_Msk | TIM_SR_CC2OF_Msk | TIM_SR_CC1OF_Msk | TIM_SR_TIF_Msk |
                   TIM_SR_CC4IF_Msk | TIM_SR_CC3IF_Msk | TIM_SR_CC2IF_Msk | TIM_SR_CC1IF_Msk | TIM_SR_UIF_Msk );
    TIM2->CNT = 0x00000000;

    // Configuration du timer (pour fonctionner comme "upcounter")
    TIM2->CR1 &= ~TIM_CR1_DIR_Msk;

    // Changement du prescale du timer
    TIM2->PSC = 80 - 1;     // Pour que le compteur change chaque microseconde, on doit
                            // diviser la fŕequence du SYSCLK (80 MHz) par 80

    // Modification de la valeur d'auto chargement
    TIM2->ARR = max_us;

    // Autorisation de la génération d'une interruption sur l'événement de "Update" du timer
    TIM2->DIER |= TIM_DIER_UIE_Msk;

    // Autorisation de l'interruption de TIM2 au niveau de NVIC
    NVIC_EnableIRQ(28);

    // Activation du timer
    TIM2->CR1 |= TIM_CR1_CEN_Msk;

}

void TIM2_IRQHandler() {

    if (TIM2->SR & TIM_SR_UIF_Msk) {  /* Cette vérification n'est pas obligatoire, puisque la seule génération d'interruption 
                                        associée au timer qu'on a autorisée était sur l'événement de mise à jour ("update")
                                        (donc, ici, si ce handler est appelé, c'est forcement en raison du mise à jour du timer) */


    /*  // ********* Code utilisé pour faire clignoter la LED en utilisant les interruptions du Timer **********

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

        TIM2->SR &= ~TIM_SR_UIF_Msk;    // "Clear" de la flag de status relative à l'interruption de mise à jour du timer

        // ********************* Fin du code utilisé pour faire clignoter la LED verte ********************* */


    /* Remarque à propos de l'implémentation suivante :
       Dans le texte du TP, il est démandé de "faire en sorte que l'affichage de la matrice soit géré par des
       interruptions du timer : affichage de l'image courante au moins 60 fois par seconde."
       Dans l'implémentation écrite ici, à chaque appel du handler d'interruption du timer, on affiche une ligne de la 
       trame courante, de manière progressive (d'une telle manière que, après 8 appels du handler, chaque ligne aura été
       appelée une fois). Dans la fonction main, on choisit le paramètre de la fonction timer_init de façon que la 
       "fréquence d'appel du handler" soit égale à 8*60 Hz (= 480 Hz), car de cette manière l'image complète (composée 
       de 8 lignes) sera affiché 60 fois par seconde. */    
    
    rgb_color pixels[8];

    static int row = 0;
    int pos = 0;

    for (int j = 0; j < 8; j++) {   
        pixels[j].r = trame[row*8*3 + pos];         // Attribution de la valeur de la LED rouge du pixel courant
        pixels[j].g = trame[row*8*3 + pos + 1];     // Attribution de la valeur de la LED verte du pixel courant
        pixels[j].b = trame[row*8*3 + pos + 2];     // Attribution de la valeur de la LED bleue du pixel courant
        pos += 3;
    }

    mat_set_row(row,pixels);
    
    if (row < 7)
        row++;
    else
        row = 0;

    TIM2->SR &= ~TIM_SR_UIF_Msk;    // "Clear" de la flag de status relative à l'interruption de mise à jour du timer

    }


}
