#include "gdt.h"
#include "types.h"

/* La GDT — 3 entrées suffisent pour nous :
   0 : segment nul (obligatoire)
   1 : segment de code kernel
   2 : segment de données kernel */
static gdt_entry_t gdt[3];
static gdt_ptr_t   gdt_ptr;

extern void gdt_load(uint32_t);  // défini dans gdt.asm

static void gdt_set_entry(int i, uint32_t base, uint32_t limit,
                           uint8_t access, uint8_t gran) {
    gdt[i].base_low   = base & 0xFFFF;
    gdt[i].base_mid   = (base >> 16) & 0xFF;
    gdt[i].base_high  = (base >> 24) & 0xFF;
    gdt[i].limit_low  = limit & 0xFFFF;
    gdt[i].granularity = ((limit >> 16) & 0x0F) | (gran & 0xF0);
    gdt[i].access     = access;
}

void gdt_init(void) {
    gdt_ptr.limit = sizeof(gdt) - 1;
    gdt_ptr.base  = (uint32_t)&gdt;

    gdt_set_entry(0, 0, 0,          0,    0);     // Segment nul
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code kernel
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Données kernel

    gdt_load((uint32_t)&gdt_ptr);
}
