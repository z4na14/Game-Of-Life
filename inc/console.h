#pragma once
#include <sys/ioctl.h>


typedef struct winsize winsize_t;
typedef struct
{
    char** screen;
    int midX;
    int midY;
    winsize_t* terminal_params;
} terminal_struct;

terminal_struct* get_terminal_ptr();

typedef void update_console_funcs(int, int);
void init_terminal();
void update_terminal(update_console_funcs function);
void print_chars(int i, int j);
void set_clear_chars(int i, int j);



