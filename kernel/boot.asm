; Multiboot 1 — compatible avec la commande "multiboot" de GRUB
section .multiboot
align 4
    dd 0x1BADB002                          ; magic Multiboot 1
    dd 0x00                                ; flags
    dd -(0x1BADB002 + 0x00)               ; checksum

; Stack
section .bss
align 16
stack_bottom:
    resb 16384
stack_top:

; Point d'entrée
section .text
global _start
extern kernel_main

_start:
    mov esp, stack_top
    call kernel_main
.hang:
    hlt
    jmp .hang