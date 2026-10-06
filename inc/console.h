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

int init_terminal(terminal_struct *terminal);
int update_console(void);