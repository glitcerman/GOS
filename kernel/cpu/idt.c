#include "idt.h"
#include "io.h"
#include "types.h"

extern void idt_load(uint32_t);
extern void irq_default_handler(void);
extern void irq1_handler(void);

struct idt_entry idt[256];
struct idt_ptr idt_reg;

void idt_set_gate(int num, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[num].base_low  = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;

    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void idt_install(void) {
    idt_reg.limit = sizeof(struct idt_entry) * 256 - 1;
    idt_reg.base  = (uint32_t)&idt;

    idt_load((uint32_t)&idt_reg);
}

void idt_init(void) {
    // Entrées 0-31 : exceptions CPU — on les laisse à 0 pour l'instant
    for (int i = 0; i < 32; i++) {
        idt_set_gate(i, 0, 0, 0);
    }

    // Entrées 32-255 : IRQ matérielles — handler par défaut
    for (int i = 32; i < 256; i++) {
        idt_set_gate(i, (uint32_t)irq_default_handler, 0x08, 0x8E);
    }

    // Clavier sur IRQ1 = entrée 33
    idt_set_gate(33, (uint32_t)irq1_handler, 0x08, 0x8E);

    idt_install();
}