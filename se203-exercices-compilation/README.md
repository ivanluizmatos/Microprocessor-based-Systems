# SE203 - Outils, langages et pratique des systèmes à microprocesseurs
## Exercices de compilation
#### Ivan Luiz DE MOURA MATOS
#### Date : 06/10/2022
___

## Exercice 1 (page 49)

Traduire en assembleur ARM le code suivant : 

```
uint32_t a; // global variable
...
for (uint8_t i=0; i<=a; i++)
g();
```

**Solution :**

```
ldr r0,=a
mov r1,#0

...

Begin:
    CMP r1,r0
    BGT End       
    BL g          @ appel de la function g (si i<=a)
    ADD r1,r1,#1  
    B Begin       

End:
    B End
    
g:
    ...
    BX lr
```

Même question si **i** est un unsigned int. Conclusion ?

**Solution :**

Si **i** est un unsigned int de 8 bits, la plus grande valeur possible de **i** (= 2^(8) - 1) est inférieure à la plus grande valeur possible de **a** (= 2^(32) - 1), car **a** possède 32 bits. Pour cette raison, dans le code présenté, si la valeur choisie pour **a** est supérieure à la valeur maximum de **i**, la condition d'arrêt de la boucle ne sera jamais atteinte (et, par conséquent, la boucle est "infinie").
Par contre, si **i** est un unsigned int de 32 bits, comme **a**, donc le "problème" mentionné ne se passera jamais.

___

## Exercice 2 (pages 50 et 51)

Traduire en assembleur ARM le code suivant : 

```
// Global variables
uint32_t *a;
uint32_t *b;
uint32_t *c;
…
*a += *c;
*b += *c;
```

**Solution :**

```
.global _start
_start:

.text

	ldr r0, .p_a
	ldr r1, .p_b
	ldr r2, .p_c

	ldr r3, [r2]
	ldr r4, [r0]
	add r4, r4, r3
	str r4, [r0]

	ldr r3, [r2]
	ldr r4, [r1]
	add r4, r4, r3
	str r4, [r1]

.data

	.p_a :
		.global a
		.word 0x00000000

	.p_b :
		.global b
		.word 0x00000004

	.p_c :
		.global c
		.word 0x00000008
```

Pourquoi GCC charge-t-il deux fois le contenu de ***c** au lieu d'une seule ?

**Solution :**

GCC charge le contenu de ***c** deux fois parce que après l'instruction ```*a += *c``` le contenu du registre qui garde la valeur de ***c** peut avoir être modifié (_"effect secondaire"_), dans le cas ou les pointeurs **a** et **c** pointent au même adresse.

___

## Exercice 1 (page 119)

1) Sur un PC Linux x86_64 actuel et par adresses croissantes, dans quel ordre sont stockées les sections suivantes : text, data*, rodata*, bss, pile et tas au moment de l’exécution ?

**Solution :**

Comme indiqué dans le cours relatif à la chaîne de compilation (page 92) :
- variables globales initialisées sont stockées dans la section **.data**,
- variables globales non initialisées sont stockées dans la section **.bss**,
- variables globales constantes sont stockées dans la section **.text / .rodata**,
- le code est stockée dans la section **.text**,
- variables locales "non static" sont stockées dans la pile (**stack**),
- 

À travers du code suivant, on peut déclarer/définir des variables des types mentionées, et ensuite vérifier leurs addresses.


```
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
```

Par exemple, en exécutant ce code, on obtient :

```
Addresse dans .text   : AF53A189 
Addresse dans .rodata : AF53B004 
Addresse dans .data   : AF53D010 
Addresse dans .bss    : AF53D018 
Addresse dans stack   : C686962C 
Addresse dans heap    : B13412A0 
```

Dans l'ordre croissant d'addresses où les sections sont stockées :

**.text < .rodata < .data < .bss < heap < stack**

___

2) Dans quel sens croît la pile ?

**Solution :**

Pour résoudre cet exercice, on peut utiliser la manière proposé en cours, où sont utilisés deux functions, **f** et **g**, pour montrer le sens de croissance de la pile. Pour cela, on peut procéder de la manière suivant : initialement, la fonction **main** appelle la fonction **f**, dans laquelle on déclare une variable (_int_) **a**; ensuite, à partir de la fonction **f**, on appelle la fonction **g**, dans laquelle on déclare une variable (_int_) **b**. Finalement, à  travers de la comparaison entre les adresses de **a** et **b**, on peut verifier le sens de croissance de la pile. Si **&a > &b**, la pile est descendante; si **&a < &b**, la pile est croissante.

```
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
```
Par exemple, une exécution de ce code a produit la sortie suivante :

```
Addresse de a: f342ba84 
Addresse de b: f342ba64
```

On vérifie que **&a > &b**, donc la pile est **descendante**.


___

## Exercice 2 (pages 120, 121 et 122)

1) Compilez sans édition de lien ce code-ci (http://bit.ly/2ApXoDl) pour ARM avec une chaîne récente, et avec les optimisations suivantes : Os, O0, O1 et O2. Pour chaque niveau d'optimisation, justifiez la taille des sections de données que vous obtenez.

**Solution :**

Pour analyser la taille des sections générées après la compilation du code `ex3.c` avec compilation, on peut utiliser le commande `size ex3.o`. On obtient, donc :

Pour l'optimisation `Os` :
```
   text    data     bss     dec     hex filename
    163       4       5     172      ac ex3.o
```

Pour l'optimisation `O0` :
```
   text    data     bss     dec     hex filename
    248       4       5     257     101 ex3.o
```

Pour l'optimisation `O1` :
```
   text    data     bss     dec     hex filename
    170       4       5     179      b3 ex3.o
```

Pour l'optimisation `O2` :
```
   text    data     bss     dec     hex filename
    170       4       5     179      b3 ex3.o
```

On peut vérifier que, pour les différents options d'optimisation, la taille des sections `data` et `bss` est constante, puisque les variables stockées (initialisées ou non initialisées) sont les mêmes n'importe pas l'optimisation choisie. Par contre, on peut observer que la taille de la section `text` change en fonction de l'optimisation utilisée, car cette taille dépende directement de la quantité d'instructions assembleur générées après la compilation du code.

___

2) Remplacez `const char mesg[]` par `static const char mesg[]`. Expliquez les différences dans les sections de données par rapport à la question précédente (elles dépendent ici aussi des optimisations).

**Solution :**

Pour l'optimisation `Os` :
```
   text    data     bss     dec     hex filename
    149       4       5     158      9e ex3.o
```

Pour l'optimisation `O0` :
```
   text    data     bss     dec     hex filename
    248       4       5     257     101 ex3.o
```

Pour l'optimisation `O1` :
```
   text    data     bss     dec     hex filename
    156       4       5     165      a5 ex3.o
```

Pour l'optimisation `O2` :
```
   text    data     bss     dec     hex filename
    156       4       5     165      a5 ex3.o
```

Par rapport à la question précédent, on peut noter que la taille des sections `data` et `bss` n'a pas changé, tandis que la taille de la section `text` a été modifiée.

___

3) Remplacez `const char mesg[]` par `const char *mesg`, puis par `const char * const mesg`. Expliquez les différences dans le code généré et les sections de données par rapport à la question 2.

**Solution :**

En raison des modifications proposées, on peut vérifier un changement dans la taille de la section `rodata`, puisque les variables constantes seront stockées dans cette section.

___