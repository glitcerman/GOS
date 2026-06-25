#include "includes/io.h"
#include "includes/shell.h"
#include "includes/terminal.h"
#include "includes/string.h"
#include "includes/DATA.h"
#include "includes/keyboard.h"
#include "includes/types.h"
#include "cpu/idt.h"
#include "cpu/gdt.h"
#include "drivers/pic.h"

extern struct idt_entry idt[];

void pic_init(void);
void idt_init(void);

void kernel_main(void) {
    terminal_clear();
    
    pic_init();
    idt_init();
    
    // Debug — affiche l'adresse de l'IDT
    char buf[16];
    uint32_t addr = (uint32_t)&idt;  // ← besoin de déclarer idt extern ici
    gdt_init();
    
    terminal_print("IDT addr: 0x");
    // Affiche les 8 chiffres hex de l'adresse
    for (int i = 7; i >= 0; i--) {
        int nibble = (addr >> (i * 4)) & 0xF;
        char c = nibble < 10 ? '0' + nibble : 'A' + nibble - 10;
        terminal_putchar(c);
    }
    terminal_print("\n");
    
    shell_init();
    __asm__ volatile ("sti");
    while (1) {}
}