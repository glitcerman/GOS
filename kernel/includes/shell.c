#include "shell.h"
#include "string.h"
#include "terminal.h"

#define BUFFER_SIZE 128

static char buffer[BUFFER_SIZE];
static int index = 0;

void shell_init(void) {
    index = 0;
    terminal_write("MyOS> ");
}

static void clear_buffer() {
    for (int i = 0; i < BUFFER_SIZE; i++)
        buffer[i] = 0;
    index = 0;
}

void shell_run_command(char *cmd) {

    if (strcmp(cmd, "help") == 0) {
        terminal_write("\nCommands:\n");
        terminal_write(" help\n echo\n clear\n");
    }
    else if (strcmp(cmd, "clear") == 0) {
        terminal_clear();
    }
    else if (string_starts_with(cmd, "echo ")) {
        terminal_write("\n");
        terminal_write(cmd + 5);
    }
    else {
        terminal_write("\nUnknown command");
    }

    terminal_write("\nGOS> ");
}

void shell_process_input(char c) {

    if (c == '\n') {
        buffer[index] = 0;
        shell_run_command(buffer);
        clear_buffer();
        return;
    }

    if (c == '\b') {
        if (index > 0) {
            index--;
            terminal_backspace();
        }
        return;
    }

    if (index < BUFFER_SIZE - 1) {
        buffer[index++] = c;
        terminal_putchar(c);
    }
}