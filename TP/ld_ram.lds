MEMORY {
    flash (rx) : ORIGIN = 0x08000000, LENGTH = 1M
    sram1 (rwx): ORIGIN = 0x20000000, LENGTH = 96K
    sram2 (rwx): ORIGIN = 0x10000000, LENGTH = 32K
}

SECTIONS {

    .table_section_flash : {    /* Cette section est utilisée pour stocker la table des vecteurs d'interruption en flash */
        _table_flash = . ;
        *(.table_section_flash)
        _etable_flash = . ;
    } > flash

    .table_section : {      /* Cette section (située en RAM) est initialisée avec une copie de la section table_section_flash */
        _table = . ;
        *(.table_section)
        _etable = . ;
    } > sram1

    .text_flash : {    /* Cette section (située en flash) est utilisée pour stocker les fonctions d'initialisation (recopie) appelées par crt0.s */
        _text_flash = . ;
        *(.text_flash)
        _etext_flash = . ;
    } > flash

    .text : {
        _text = . ;
        *(.text)
        _etext = . ;
    } > sram1 AT > flash

    .rodata : {
        *(.rodata)
        _erodata = . ;
    } > flash

    .data : AT( ADDR(.rodata) + SIZEOF(.rodata) ) {
        _data = . ;
        *(.data)
        _edata = . ;
    } > sram1
    
    .bss : {
        __bss_start = .;
        *(.bss) *(COMMON)
        __bss_end = .;
    } > sram1
}

ENTRY(_start)

_stack_start = ORIGIN(sram2) + LENGTH(sram2);

_text_LMA = LOADADDR(.text);    /* _text_LMA réprésente l'adresse de début de la section .text en flash */