#pragma once
#include <sys/ioctl.h>


typedef struct winsize winsize_t;
typedef struct
{
    char** screen;
    // TODO: define middle character
    int midX;
    int midY;
    winsize_t* terminal_params;
} terminal_struct;

typedef void (update_console_funcs)(terminal_struct*, int, int);

void update_terminal(terminal_struct *terminal, update_console_funcs function);
void print_chars(terminal_struct *terminal, int i, int j);
void set_clear_chars(terminal_struct *terminal, int i, int j);


