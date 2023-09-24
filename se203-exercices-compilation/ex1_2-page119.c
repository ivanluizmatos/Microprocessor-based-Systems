



/*
Pour résoudre cet exercice, on peut utiliser la manière proposé en cours, 
où sont utilisés deux functions, **f** et **g**, pour montrer le sens de 
croissance de la pile. Pour cela, on procède de la manière suivant : 
initialement, dans la fonction **f**, on déclare un pointeur **pa** vers 
une variable **a**; ensuite, on appelle la fonction **g**, dans laquelle 
on déclare un pointeur **pb** vers une variable **b**. Finalement, à  
travers de la comparaison entre les adresses de **a** et **b**, on peut 
verifier le sens de croissance de la pile. Si **&a > &b**, la pile est 
descendant; si **&a < &b**, la pile est croissante.
*/



/*
#include <stdio.h>

int * g() {

    int b;
    return (&b);
    
}

void f() {

    int a;
    int *pa = &a;
    int *pb = g();

    printf("&a = %x , &b = %x",pa,pb);

    if (pa < pb){
        printf("La pile est croissante.");
    }
    else {
        printf("La pile est descendant.");
    }

}

int main() {

    f();

    return 0;
}



*/




#include <stdio.h>

void g() {

    int b;
    printf("Addresse de b: %x \n",&b);

}

void f() {

    int a;
    printf("Addresse de a: %x \n",&a);

    g();

}

int main() {

    f();

    return 0;
}