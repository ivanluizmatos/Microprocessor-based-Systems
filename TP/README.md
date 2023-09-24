# Travail pratique (TP) : Développement sur carte nue (bare-metal)

Le but de ce projet est :

- de se familiariser avec la cross-compilation
- d'avoir une première expérience de développement sur carte nue (bare-metal).

Nous allons développer sur des cartes STM32 IoT Node.


**Tâches (cf. site du cours) :**

1. Introduction
    - Documentation
    - Outils de débug
    - Branchement de la carte
    - Mapping mémoire
    - Pilotage de la sonde
2. Création d'un exécutable
    - Mapping mémoire
    - Linker script
    - Programme de base
    - Programme plus évolué
3. GPIO
    - Multiplexage des broches
    - Clock gating
    - LED verte
    - LED bleue/jaune
4. Horloges
5. CMSIS
6. UART
    - Le protocole
    - Utilisation
    - Configuration
    - Envoi et réception
    - Tests
    - Avant de continuer
7. Afficheur à LED
    - Fonctionnement de la matrice
    - Contrôleur de LED
    - Connexion sur la carte
    - Contrôle de base
    - Premier test
    - Image statique
8. IRQ
    - Exceptions sur les Cortex-M
    - Traitement d'une exception
    - NVIC
    - Mise en place
    - GPIO+IRQ
9. UART+IRQ+LED
10. Timers
11. Mise en flash
