#include "keyboard.h"
#include "io.h"
#include "shell.h"

#define KEYBOARD_PORT 0x60

static char scancode_to_ascii[128] = {
    0, 27, '1','2','3','4','5','6','7','8','9','0','-','=', '\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,'\\','z','x','c','v','b','n','m',',','.','/'
};

void keyboard_handler(void) {
    unsigned char sc = inb(KEYBOARD_PORT);

    if (sc & 0x80)
        return;

    char c = scancode_to_ascii[sc];

    if (c != 0) {
        shell_process_input(c);   // 👈 lien direct shell
    }

    outb(0x20, 0x20);
}