#include <stdint.h>

static uint16_t* video = (uint16_t*)0xB8000;
static int row = 0;
static int col = 0;

static void put_char(char c) {
    video[row * 80 + col] = (0x0F << 8) | c;
}

void terminal_putchar(char c) {
    if (c == '\n') {
        row++;
        col = 0;
        return;
    }

    put_char(c);
    col++;
    if (col >= 80) {
        col = 0;
        row++;
    }
}

void terminal_print(char *str) {
    while (*str)
        terminal_putchar(*str++);
}

void terminal_clear() {
    for (int i = 0; i < 80 * 25; i++)
        video[i] = (0x0F << 8) | ' ';
    row = 0;
    col = 0;
}

void terminal_backspace() {
    if (col > 0) {
        col--;
        video[row * 80 + col] = (0x0F << 8) | ' ';
    }
}