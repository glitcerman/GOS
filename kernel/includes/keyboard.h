#ifndef KEYBOARD_H
#define KEYBOARD_H

void keyboard_init(void);
void keyboard_handler(void);

char keyboard_getchar(void);
int keyboard_has_input(void);

#endif