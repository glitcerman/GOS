#include "includes/io.h"
#include "includes/shell.h"
#include "includes/terminal.h"
#include "includes/string.h"
#include "includes/DATA.h"
#include "drivers/pic.h"
#include "cpu/idt.h"
#include "includes/keyboard.h"
#include "includes/types.h"

void pic_init(void);
void idt_init(void);

void kernel_main(void) {

    pic_init();
    idt_init();

    shell_init();

    __asm__ volatile ("sti");

    while (1) {
        // tout se passe via interruptions
    }
}