#include "console.h"
#include <stdio.h>
#include <stdlib.h>


// Set variables as global as they will be used by all functions
winsize_t terminal_params; // Here are stored the terminal parameters
terminal_struct terminal;
terminal_struct* terminal_ptr = &terminal;

// Function used to get the pointer to the terminal outside the file
terminal_struct* get_terminal_ptr(){return terminal_ptr;}


/* Function: init_terminal
 * ---------------------
 * Gets the execution terminal parameters and sets the screen
 *
 * returns: nothing
*/

void init_terminal()
{
    // Get the struct with the size of the console
    ioctl(0, TIOCGWINSZ, &terminal_params);

    terminal_ptr -> midX = terminal_params.ws_col / 2,
    terminal_ptr -> midY = terminal_params.ws_row / 2;
    terminal_ptr -> terminal_params = &terminal_params;

    // Allocate space for all the columns the terminal has
    terminal_ptr -> screen = malloc(terminal_params.ws_row * sizeof(char*));
    for (int i = 0; i < terminal_params.ws_row; i++) {
        terminal_ptr -> screen[i] = malloc(terminal_params.ws_col * sizeof(char));
    }

}

void get_user_pattern(terminal_struct *terminal)
{
    int row = 0;
    char line[terminal -> terminal_params -> ws_col];
    fgets(line,terminal -> terminal_params -> ws_col,stdin);

    while (line != NULL)
    {
        strcpy(terminal -> screen[row], line);
        fgets(line,terminal -> terminal_params -> ws_col,stdin);
    }
}

/* Function: update_terminal
 * ---------------------
 * Writes to the screen array of the terminal struct the updated instance
 *
 * function: Operation to perform on the screen
 *
 * returns: nothing
*/

void update_terminal(update_console_funcs function)
{
    printf("\e[1;1H\e[2J");
    for (int i = 0; i < terminal_ptr -> terminal_params -> ws_row; i++)
    {
        for (int j = 0; j < terminal_ptr -> terminal_params -> ws_col; j++)
        {
            function(i, j);
        }
        printf("\n");
    }

    printf("\n");
}

void set_clear_chars(int i, int j)
{
    terminal_ptr -> screen[i][j] = ' ';
}

void print_chars(int i, int j)
{
    printf("%c", terminal_ptr -> screen[i][j]);
}
