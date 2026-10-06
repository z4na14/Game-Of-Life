#include "console.h"
#include <stdio.h>


int init_terminal(terminal_struct *terminal)
{
    printf("\e[1;1H\e[2J");
    for (int i = 0; i < terminal -> terminal_params -> ws_row; i++)
    {
        for (int j = 0; j < terminal -> terminal_params -> ws_col; j++)
        {
            terminal -> screen[i][j] = ' ';
            printf(" ");
        }
        printf("\n");
    }

    printf("\n");
    return 0;
}
