#include <stddef.h>
#include <stdint.h>
#include <string.h>

void *memset(void *s, int c, size_t n) {

    /*
    DESCRIPTION:
    The memset() function fills the first n bytes of the memory area 
    pointed to by s with the constant byte c.
    */
    
    uint8_t *p = (uint8_t *) s;
    int i;

    for (i = 0; i < (int) n; i++) {
        p[i] = (uint8_t) c;   // *(p + i) = (uint8_t) c;
    }
    
    return s;

}


void *memcpy(void *dest, const void *src, size_t n) {

    /*
    DESCRIPTION:
    The  memcpy()  function  copies n bytes from memory area src 
    to memory area dest.  The memory areas must not overlap. 
    Use memmove() if the memory areas do overlap.
    */

    uint8_t *pd = (uint8_t *) dest;
    uint8_t *ps = (uint8_t *) src;

    int i;

    if ( !(ps + n-1 >= pd) && !(pd + n-1 >= ps) ) { // S'il n'y a pas d'overlap

       for (i = 0; i < (int) n; i++) {
            pd[i] = ps[i];  // *(pd + i) = *(ps + i);
        }

    }

    else {  // S'il y a overlap
        memmove(dest,src,n); // Appel de memmove
    }

    return dest;

}


void *memmove(void *dest, const void *src, size_t n) {

    /*
    DESCRIPTION:
    The  memmove() function copies n bytes from memory area src 
    to memory area dest.  The memory areas may overlap: copying 
    takes place as though the bytes in src are first copied into
    a temporary array  that  does  not overlap src or dest, and 
    the bytes are then copied from the temporary array to dest.
    */

    uint8_t *pd = (uint8_t *) dest;
    uint8_t *ps = (uint8_t *) src;

    int i;

    // L'occurrence d'overlap est vérifié à travers de la comparaison
    // entre les adresses de début et fin des régions "source" et 
    // "destination"

    if (ps + n-1 >= pd) {         // Premier cas d'overlap
        // La copie commence à partir de la dernière adresse 
        // de la region "source"
        for (i = n-1; i >= 0; i--) {
            pd[i] = ps[i];        // *(pd + i) = *(ps + i);
        }
    }

    else if (pd + n-1 >= ps) {    // Deuxième cas d'overlap
        // La copie commence à partir de la première adresse 
        // de la region "source"
        for (i = 0; i < (int) n; i++) {
            pd[i] = ps[i];        // *(pd + i) = *(ps + i);
        }
    }

    else {                       // S'il n'y a pas d'overlap
        for (i = 0; i < (int) n; i++) {
            pd[i] = ps[i];       // *(pd + i) = *(ps + i);
        }
    }

    return dest;

}


int memcmp(const void *s1, const void *s2, size_t n){

    /*
    DESCRIPTION:
    The  memcmp() function compares the first n bytes (each 
    interpreted as unsigned char) of the memory areas s1 and s2.
    The memcmp() function returns an integer less than, equal to, 
    or greater than zero if the first n  bytes of s1 is found, 
    respectively, to be less than, to match, or be greater than 
    the first n bytes of s2.
    */

    uint8_t *ps1 = (uint8_t *) s1;
    uint8_t *ps2 = (uint8_t *) s2;

    int i;

    if (n == 0) {
        return 0;
    }

    for (i = 0; i < (int) n; i++) {

        if (ps1[i] > ps2[i]) {
            // La fonction retourne une valeur positive (ici, égale à 1) si
            // les n premiers bytes de s1 représentent un nombre plus grand
            // que le nombre représenté par les n premiers bits de s2. 
            return 1;
        }

        else if (ps1[i] < ps2[i]) {
            // La fonction retourne une valeur negative (ici, égale à -1) si
            // les n premiers bytes de s1 représentent un nombre moins grand
            // que le nombre représenté par les n premiers bits de s2. 
            return -1;
        }
    }

    // Si tous les bytes correspondents de s1 et s2 sont égals, donc le 
    // programme sortira de la boucle for, et la fonction retournera la 
    // valeur 0
    return 0;

}
