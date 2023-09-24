#include <stdio.h>
#include <stdlib.h>

int globale_initialisee = 10; 
int globale_non_initialisee;
const int globale_constante = 20;

int f() {
    return 1;
}

int main() {
    
    int locale_initialisee = 30;

    char *pointeur = malloc(sizeof(char));

    printf("Addresse dans .text   : %X \n",&f);
    printf("Addresse dans .rodata : %X \n",&globale_constante);  
    printf("Addresse dans .data   : %X \n",&globale_initialisee);
    printf("Addresse dans .bss    : %X \n",&globale_non_initialisee);
    printf("Addresse dans stack   : %X \n",&locale_initialisee);
    printf("Addresse dans heap    : %X \n",pointeur);

    return 0;
}