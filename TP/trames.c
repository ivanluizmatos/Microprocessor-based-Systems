#include "trames.h"

// Fonction pour activer le traitement de l'interruption associée 
// à la réception d'un caractère à travers de l'UART
void usart_interrupt_enable() {

    USART1->CR1 |= USART_CR1_RXNEIE_Msk;    // (cf. page 1378 du manuel)
    NVIC_EnableIRQ(37);                     // (cf. page 397)

    USART1->CR3 |= USART_CR3_EIE_Msk;       // (cf. page 1387)

}

// Tâche de réception du port série (Handler d'IRQ associé à l'UART) 
void USART1_IRQHandler() {

/*  // Code relatif à la partie UART_IRQ_1
    static int pos_trame = 0;

    char new_byte = uart_getchar();

    if (new_byte != 0xff) {
        trame[pos_trame] = new_byte;
        pos_trame++;
    }
    else
        pos_trame = 0;
    
    // Fin du code relatif à la partie UART_IRQ_1
*/


    static int pos_trame = 0;   // 'pos_trame' indique la position courante de la trame qui sera mise à jour
    
    static int ignore = 0;      // 'ignore' indique s'il y a eu une erreur. Si ignore == 1, on ignore la trame courante.
                                //  Remarque: ici, "ignorer" veut dire qu'on ne met pas à jour la trame courante (c'est-à-dire,
                                //  on n'ajoute pas de nouveaux octects reçus à la trame) après la  détection d'une erreur.
                                //  S'il y a eu une erreur : On attend le début de la prochaine trame, en affichant l'état de
                                //  la trame courante avant l'erreur.

    char new_byte = uart_getchar();

    if ( USART1->ISR & (USART_ISR_FE_Msk | USART_ISR_ORE_Msk) ) { // vérification d'erreur de framing (FE) ou d'overrun (ORE) 
        ignore = 1;     // On fait ignore = 1, pour indiquer l'occurence d'une erreur, et pour que la trame courante soit "ignorée"
        USART1->ICR |= (USART_ICR_FECF | USART_ICR_ORECF);  // On fait le clear des bits de USART_ISR qui indiquent l'erreurs FE ou ORE 
    }

    if (!ignore && new_byte != 0xff) {  // On mettre à jour la trame (image) courante dès qu'il n'y a pas eu d'erreur (ignore==0)
        trame[pos_trame] = new_byte;
        pos_trame++;
    }

    if (new_byte == 0xff) {
        
        pos_trame = 0;
        
        if (ignore)
            ignore = 0;     // Pour la nouvelle trame, on fait ignore = 0, afin de pouvoir afficher la nouvelle trame

    }

}

// Tâche d'affichage (pour afficher la trame courante)
void afficher_image_statique(volatile uint8_t image[192]) {

    rgb_color pixels[8];    // Le vecteur 'pixels' corresponde aux pixels d'une
                            // ligne 'i' de la matrice.

    while(1) {

        int pos = 0;

        // Boucles imbriquées pour  définir la "valeur" de chaque pixel (i,j).
        // Dans la boucle interne, on attribue la valeur de chaqu'un des LEDs
        // (R, G et B) qui composent le pixel courant (c'est-à-dire: le pixel
        // situé dans la colonne j et la ligne i).
        for (int i = 0; i < 8; i++) { 
            for (int j = 0; j < 8; j++) {   
                pixels[j].r = image[pos];         // Attribution de la valeur de la LED rouge du pixel courant
                pixels[j].g = image[pos + 1];     // Attribution de la valeur de la LED verte du pixel courant
                pixels[j].b = image[pos + 2];     // Attribution de la valeur de la LED bleue du pixel courant
                pos += 3;
            }

            mat_set_row(i,pixels);      // Allume la ligne courant (i) de la matrice 
            
            for (int j=0; j<3000; j++)  // Boucle d'attente entre l'allumage de lignes successives
                asm volatile("nop");
        }

    }

}
