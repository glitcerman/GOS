#include "keyboard.h"
#include "io.h"
#include "shell.h"
#include "terminal.h"

#define KEYBOARD_PORT 0x60

static char scancode_to_ascii[128] = {
    0,    // 0x00
    27,   // 0x01 - Echap
    '1',  // 0x02
    '2',  // 0x03
    '3',  // 0x04
    '4',  // 0x05
    '5',  // 0x06
    '6',  // 0x07
    '7',  // 0x08
    '8',  // 0x09
    '9',  // 0x0A
    '0',  // 0x0B
    '-',  // 0x0C
    '=',  // 0x0D
    '\b', // 0x0E - Backspace
    '\t', // 0x0F - Tab
    'a',  // 0x10
    'z',  // 0x11
    'e',  // 0x12
    'r',  // 0x13
    't',  // 0x14
    'y',  // 0x15
    'u',  // 0x16
    'i',  // 0x17
    'o',  // 0x18
    'p',  // 0x19
    '^',  // 0x1A
    '$',  // 0x1B
    '\n', // 0x1C - Entrée
    0,    // 0x1D - Ctrl
    'q',  // 0x1E
    's',  // 0x1F
    'd',  // 0x20
    'f',  // 0x21
    'g',  // 0x22
    'h',  // 0x23
    'j',  // 0x24
    'k',  // 0x25
    'l',  // 0x26
    'm',  // 0x27
    0,    // 0x28
    '`',  // 0x29
    0,    // 0x2A - Shift gauche
    '*',  // 0x2B
    'w',  // 0x2C
    'x',  // 0x2D
    'c',  // 0x2E
    'v',  // 0x2F
    'b',  // 0x30
    'n',  // 0x31
    ',',  // 0x32
    ';',  // 0x33
    ':',  // 0x34
    '!',  // 0x35
    0,    // 0x36 - Shift droit
    '*',  // 0x37
    0,    // 0x38 - Alt
    ' ',  // 0x39 - Espace
};

void keyboard_handler(void) {
    unsigned char sc = inb(KEYBOARD_PORT);

    if (!(sc & 0x80)) {
        char c = scancode_to_ascii[sc];
        if (c != 0) {
            shell_process_input(c);
        }
    }

    outb(0x20, 0x20);
}