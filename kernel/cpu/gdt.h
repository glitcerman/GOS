#ifndef GDT_H
#define GDT_H

#include "types.h"

/* Une entrée de la GDT — 8 octets */
typedef struct {
    uint16_t limit_low;    // Bits 0-15 de la limite
    uint16_t base_low;     // Bits 0-15 de la base
    uint8_t  base_mid;     // Bits 16-23 de la base
    uint8_t  access;       // Permissions
    uint8_t  granularity;  // Taille + bits 16-19 de la limite
    uint8_t  base_high;    // Bits 24-31 de la base
} __attribute__((packed)) gdt_entry_t;

/* Pointeur GDT — donné au CPU avec lgdt */
typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) gdt_ptr_t;

void gdt_init(void);

#endif
