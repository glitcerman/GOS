#ifndef SHELL_H
#define SHELL_H

void shell_init(void);
void shell_process_input(char c);
void shell_run_command(char *cmd);

#endif