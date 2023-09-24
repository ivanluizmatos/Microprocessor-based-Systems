    .syntax unified
    .global _start
    .thumb
#    .arch armv7-m
#    .cpu cortex-m4 

.section .text_flash,"ax", %progbits

.thumb_func
_start:
    ldr sp, =_stack_start

    bl move_text
    bl move_table
    bl init_bss
    bl move_data

    bl main

_exit:
    b _exit
