#include <stdint.h>
#include "pic.h"

#define PIC1_COMMAND 0x20
#define PIC1_DATA    0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA    0xA1

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void pic_remap(int offset1, int offset2) {
    // Pas de sauvegarde des masques !

    outb(PIC1_COMMAND, 0x11);
    outb(PIC2_COMMAND, 0x11);

    outb(PIC1_DATA, offset1);
    outb(PIC2_DATA, offset2);

    outb(PIC1_DATA, 4);
    outb(PIC2_DATA, 2);

    outb(PIC1_DATA, 0x01);
    outb(PIC2_DATA, 0x01);

    // Masques mis à 0xFF par défaut — pic_init s'en occupe
    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);
}

void pic_init() {
    pic_remap(32, 40);
    
    // Masquer toutes les IRQ sauf IRQ1 (clavier)
    outb(0x21, 0xFD);  // 1111 1101 — seul bit 1 à 0 = clavier actif
    outb(0xA1, 0xFF);  // Tout masqué sur le PIC esclave
}