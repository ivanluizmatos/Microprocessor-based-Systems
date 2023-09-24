extern char __bss_start, __bss_end,
            _data, _edata, _erodata,
            _table, _etable,
            _text, _etext,
            _text_LMA, _table_flash;

// Fonction pour faire l'initialisation de la région bss, en écrivant 
// la valeur 0 dans toutes les positions dans cette région
void __attribute__((section(".text_flash"))) init_bss(){

    char *p = &__bss_start; 

    while(p < &__bss_end){
        *p = 0; 
        p++;
    }

}

    /*
    Remarque (à propos de la fonction init_bss) :
    Si on fait la déclaration 'char *p' avant la fonction init_bss() et après
    on fait 'p = &__bss_start' dans la fonction init_bss(), le code n'aura pas
    le fonctionnement désiré. Cela est dû au fait que, dans ce cas, l'adressse
    de la variable non initialisée p (qui est un pointeur) sera initialement placée
    dans la section bss. Puisque p est utilisé pour mettre 0 dans les positions de 
    mémoire de bss, il va avoir un moment où p va pointer vers lui même, et il va 
    modifier sa propre valeur (*p <-- 0). Par conséquent, p passera à pointer vers
    la position 0 de mémoire et restera indéfiniment dans cette position.
    */


// Fonction pour déplacer (copier) le contenu de la région data depuis la flash et vers la RAM
void __attribute__((section(".text_flash"))) move_data() {

    char *src = &_erodata;
    char *dst = &_data;

    while (dst < &_edata) {
        *dst = *src;
        dst++;
        src++;
    }
}

// Fonction pour déplacer (copier) la table des vecteurs d'interruption depuis la flash et vers la RAM
void __attribute__((section(".text_flash"))) move_table() {

    char *src = &_table_flash;
    char *dst = &_table;

    while (dst < &_etable) {
        *dst = *src;
        dst++;
        src++;
    }

}


// Fonction pour déplacer (copier) le contenu de la région text depuis la flash et vers la RAM
void __attribute__((section(".text_flash"))) move_text() {

    char *src = &_text_LMA;
    char *dst = &_text;

    while (dst < &_etext) {
        *dst = *src;
        dst++;
        src++;
    }

}
