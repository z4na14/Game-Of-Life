#include "console.h"
#include <stdio.h>


void set_clear_chars(terminal_struct *terminal, int i, int j)
{
    terminal -> screen[i][j] = ' ';
}

void print_chars(terminal_struct *terminal, int i, int j)
{
    printf("%c", terminal -> screen[i][j]);
}

void update_terminal(terminal_struct *terminal, update_console_funcs function)
{
    printf("\e[1;1H\e[2J");
    for (int i = 0; i < terminal -> terminal_params -> ws_row; i++)
    {
        for (int j = 0; j < terminal -> terminal_params -> ws_col; j++)
        {
            function(terminal, i, j);
        }
        printf("\n");
    }

    printf("\n");
}
