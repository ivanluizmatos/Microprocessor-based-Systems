#include "matrix.h"

#define CLK_FREQ 80000000   // Fréquence du clock : 80 MHz

void matrix_init() {

    // Activation des horloges des ports A, B et C (cf. page 252 du manuel de référence)
    RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOAEN | RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN);

    // Configuration de toutes les broches GPIO reliées au driver en mode output
    GPIOA->MODER = ( GPIOA->MODER & ~(GPIO_MODER_MODE2 | GPIO_MODER_MODE3 | GPIO_MODER_MODE4 | GPIO_MODER_MODE5 | 
                                    GPIO_MODER_MODE6 | GPIO_MODER_MODE7 | GPIO_MODER_MODE15) )
                  | GPIO_MODER_MODE2_0 | GPIO_MODER_MODE3_0 | GPIO_MODER_MODE4_0 | GPIO_MODER_MODE5_0
                  | GPIO_MODER_MODE6_0 | GPIO_MODER_MODE7_0 | GPIO_MODER_MODE15_0;
    
    GPIOB->MODER = ( GPIOB->MODER & ~(GPIO_MODER_MODE0 | GPIO_MODER_MODE1 | GPIO_MODER_MODE2) )
                  | GPIO_MODER_MODE0_0 | GPIO_MODER_MODE1_0 | GPIO_MODER_MODE2_0;

    GPIOC->MODER = ( GPIOC->MODER & ~(GPIO_MODER_MODE3 | GPIO_MODER_MODE4 | GPIO_MODER_MODE5) )
                  | GPIO_MODER_MODE3_0 | GPIO_MODER_MODE4_0 | GPIO_MODER_MODE5_0;        

    // Configuration des broches GPIO en vitesse maximale
    GPIOA->OSPEEDR |= GPIO_MODER_MODE2 | GPIO_MODER_MODE3 | GPIO_MODER_MODE4 | GPIO_MODER_MODE5 | 
                     GPIO_MODER_MODE6 | GPIO_MODER_MODE7 | GPIO_MODER_MODE15;
    
    GPIOB->OSPEEDR |= GPIO_MODER_MODE0 | GPIO_MODER_MODE1 | GPIO_MODER_MODE2;

    GPIOC->OSPEEDR |= GPIO_MODER_MODE3 | GPIO_MODER_MODE4 | GPIO_MODER_MODE5;

    // Initialization des sorties
    RST(0);
    LAT(1);
    SB(1);
    SCK(1);
    SDA(1);
    ROW0(0); ROW1(0); ROW2(0); ROW3(0); ROW4(0); ROW5(0); ROW6(0); ROW7(0);

    // Boucle d'attente
    for (int i = 0; i < CLK_FREQ/10; i++) {
        asm volatile ("nop");
    }

    // RST à l'état haut
    RST(1);

    // Initialisation du BANK0
    init_bank0();               // (Cette fonction est définie après)

}

void RST(char x) {  // Fonction pour contrôler la broche RST
    if(x)
        GPIOC->BSRR = GPIO_BSRR_BS3;
    else
        GPIOC->BSRR = GPIO_BSRR_BR3;
}

void SB(char x) {   // Fonction pour contrôler la broche SB
    if(x)
        GPIOC->BSRR = GPIO_BSRR_BS5;
    else    
        GPIOC->BSRR = GPIO_BSRR_BR5;
}

void LAT(char x) {  // Fonction pour contrôler la broche LAT
    if(x)
        GPIOC->BSRR = GPIO_BSRR_BS4;
    else    
        GPIOC->BSRR = GPIO_BSRR_BR4;
}

void SCK(char x) {  // Fonction pour contrôler la broche SCK
    if(x)
        GPIOB->BSRR = GPIO_BSRR_BS1;
    else    
        GPIOB->BSRR = GPIO_BSRR_BR1;
}

void SDA(char x) {  // Fonction pour contrôler la broche SDA
    if(x)
        GPIOA->BSRR = GPIO_BSRR_BS4;
    else    
        GPIOA->BSRR = GPIO_BSRR_BR4;
}

void ROW0(char x) { // Fonction pour activer/désactiver la ligne 0
    if(x)
        GPIOB->BSRR = GPIO_BSRR_BS2;
    else    
        GPIOB->BSRR = GPIO_BSRR_BR2;
}

void ROW1(char x) { // Fonction pour activer/désactiver la ligne 1
    if(x)
        GPIOA->BSRR = GPIO_BSRR_BS15;
    else    
        GPIOA->BSRR = GPIO_BSRR_BR15;
}

void ROW2(char x) { // Fonction pour activer/désactiver la ligne 2
    if(x)
        GPIOA->BSRR = GPIO_BSRR_BS2;
    else    
        GPIOA->BSRR = GPIO_BSRR_BR2;
}

void ROW3(char x) { // Fonction pour activer/désactiver la ligne 3
    if(x)
        GPIOA->BSRR = GPIO_BSRR_BS7;
    else    
        GPIOA->BSRR = GPIO_BSRR_BR7;
}

void ROW4(char x) { // Fonction pour activer/désactiver la ligne 4
    if(x)
        GPIOA->BSRR = GPIO_BSRR_BS6;
    else    
        GPIOA->BSRR = GPIO_BSRR_BR6;
}

void ROW5(char x) { // Fonction pour activer/désactiver la ligne 5
    if(x)
        GPIOA->BSRR = GPIO_BSRR_BS5;
    else    
        GPIOA->BSRR = GPIO_BSRR_BR5;
}

void ROW6(char x) { // Fonction pour activer/désactiver la ligne 6
    if(x)
        GPIOB->BSRR = GPIO_BSRR_BS0;
    else    
        GPIOB->BSRR = GPIO_BSRR_BR0;
}

void ROW7(char x) { // Fonction pour activer/désactiver la ligne 7
    if(x)
        GPIOA->BSRR = GPIO_BSRR_BS3;
    else    
        GPIOA->BSRR = GPIO_BSRR_BR3;
}

void pulse_SCK() {  // Fonction qui effectue un pulse positif sur SCK
    SCK(0);
    SCK(1);
    SCK(0);
}

void pulse_LAT() {  // Fonction qui effectue un pulse négatif sur LAT
    LAT(1);
    LAT(0);
    LAT(1);
}

void deactivate_rows() {    // Fonction qui éteint toutes les lignes

    ROW0(0);
    ROW1(0);
    ROW2(0);
    ROW3(0);
    ROW4(0);
    ROW5(0);
    ROW6(0);
    ROW7(0);
}

void activate_row(int row) {  // Fonction pour activer une ligne (row) choisie

        if (row == 0) {
            ROW0(1); 
            return;
        }
        else if (row == 1) {
            ROW1(1); 
            return;
        }
        else if (row == 2) {
            ROW2(1); 
            return;
        }
        else if (row == 3) {
            ROW3(1); 
            return;
        }
        else if (row == 4) {
            ROW4(1); 
            return;
        }
        else if (row == 5) {
            ROW5(1);
            return;
        }
        else if (row == 6) {
            ROW6(1); 
            return;
        }
        else if (row == 7) {
            ROW7(1); 
            return;
        }
    }

void send_byte(uint8_t val, int bank) {   // Fonction pour envoyer 8 bits consécutifs (val)
                                          // au bank spécifié par le paramètre bank

    if (bank == 1) {
        SB(1);
        for (int i = 7; i >= 0; i--) {
            SDA(val & (0b1 << i));
            pulse_SCK();
        }
    }

    else if (bank == 0) {
        SB(0);
        for (int i = 5; i >= 0; i--) {
            SDA(val & (0b1 << i));
            pulse_SCK();
        }
    }

}

void mat_set_row(int row, const rgb_color *val) {   // Fonction qui allume la ligne (row) selon
                                                    // les valeurs spécifiees dans le tableau val  

    for (int i = 7; i >= 0; i--) {
            send_byte(val[i].b, 1);
            send_byte(val[i].g, 1);
            send_byte(val[i].r, 1);
    }

    /* On est intéressé à allumer une seule ligne à chaque instant, 
    parce que tous les LEDs d'une même colonne seraient allumées avec 
    la même couleur si les lignes correspondants étaient activées. Pour 
    cette raison, on appele deactivate_rows() ici, avant d'allumer la ligne. */
    deactivate_rows();  

    // Puisque la désactivation des lignes prend un certain temps,
    // on fait ici une boucle d'attente
    for (int j=0; j<100; j++)
        asm volatile("nop");

    pulse_LAT();
    activate_row(row);

}


void init_bank0() {     // Fonction pour mettre tous les six bits du BANK0 à 1

    for (int i = 0; i < 24; i++) {
        send_byte(0b111111, 0);
    }

    pulse_LAT();
}

void test_pixels() {

    /* Fonction de teste : les lignes sont allumées successivement (en commençant par la première, en haut). 
       Chaque ligne est composée par la (même) séquence de couleurs : R-G-B-R-G-B-R-G. Après l'allumage de la dernière
       ligne (en bas), les lignes sont successivement allumées de nouveau, mais en commençant par la dernière ligne
       et en direction à la première. Le processus se répète. */

    rgb_color pixels[8];

    pixels[0].r = 0xFF; pixels[0].g = 0;    pixels[0].b = 0;
    pixels[1].r = 0;    pixels[1].g = 0xFF; pixels[1].b = 0;
    pixels[2].r = 0;    pixels[2].g = 0;    pixels[2].b = 0xFF;
    pixels[3].r = 0xFF; pixels[3].g = 0;    pixels[3].b = 0;
    pixels[4].r = 0;    pixels[4].g = 0xFF; pixels[4].b = 0;
    pixels[5].r = 0;    pixels[5].g = 0;    pixels[5].b = 0xFF;
    pixels[6].r = 0xFF; pixels[6].g = 0;    pixels[6].b = 0;
    pixels[7].r = 0;    pixels[7].g = 0xFF; pixels[7].b = 0;

   // const rgb_color *val = pixels;    

    while(1) {

        for(int i = 0; i < 8; i++) {
            mat_set_row(i,pixels);
            for (int j=0; j<1500000; j++)
                asm volatile("nop");
            //deactivate_rows();
        }

       for(int i = 7; i >= 0; i--) {
            mat_set_row(i,pixels);
            for (int j=0; j<1500000; j++)
                asm volatile("nop");
            //deactivate_rows();
       }
       
    }
}


void test_image_statique() {

    uint8_t *p;     // On utilise un pointeur p pour parcourir le contenu
                    // stockée dans la mémoire et provenant du fichier binaire
                    // image.raw fourni.

    rgb_color pixels[8];    // Le vecteur 'pixels' corresponde aux pixels d'une
                            // ligne 'i' de la matrice.

    while(1) {

        p = &_binary_image_raw_start;   // Pointeur p initialement pointe vers
                                        // le début de la région de mémoire qui
                                        // contient les valeus de chaque pixel

        // Boucles imbriquées pour  définir la "valeur" de chaque pixel (i,j).
        // Dans la boucle interne, on attribue la valeur de chaqu'un des LEDs
        // (R, G et B) qui composent le pixel courant (c'est-à-dire: le pixel
        // situé dans la colonne j et la ligne i).
        for (int i = 0; i < 8; i++) { 
            for (int j = 0; j < 8; j++) {   
                pixels[j].r = *p;           // Attribution de la valeur de la LED rouge du pixel courant
                pixels[j].g = *(p + 1);     // Attribution de la valeur de la LED verte du pixel courant
                pixels[j].b = *(p + 2);     // Attribution de la valeur de la LED bleue du pixel courant
                p += 3;
            }

            mat_set_row(i,pixels);      // Allume la ligne courant (i) de la matrice 
            
            for (int j=0; j<3000; j++)  // Boucle d'attente entre l'allumage de lignes successives
                asm volatile("nop");
        }

    }

}
