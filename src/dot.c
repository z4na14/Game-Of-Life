#include "dot.h"
#include <stdio.h>


int num_of_active_dots;
dot_ptr active_nodes[100];


/* Function: matrix_init
 * ---------------------
 * Initialize the matrix of dots using the pattern inputted by the used
 *
 * *pattern[]: Array of strings that contains the pattern
 * pattern_size_X: The number of columns the pattern has
 * pattern_size_Y: The number of rows the pattern has
 * *terminal: The terminal struct to change the outputted values
 *
 * returns: nothing
*/

void matrix_init(char *pattern[], int pattern_size_X, int pattern_size_Y, terminal_struct* terminal)
{
    // Define the middle part for the terminal and the pattern to do the calculations
    int midX = terminal -> midX, midY = terminal -> midY;
    int mid_patternX = pattern_size_X / 2;
    int mid_patternY = pattern_size_Y / 2;

    for (int i = 0; i < pattern_size_Y; i++)
    {
        for (int j = 0; j < pattern_size_X; j++)
        {
            if (pattern[i][j] == '*')
            {
                // Create the new dot instance
                dot_t dot = {.posX = (j < mid_patternX) ? midX - (mid_patternX - j) : midX + (j - mid_patternX),
                             .posY = (i < mid_patternY) ? midY - (mid_patternY - i) : midY + (i - mid_patternY)};
                //.neighbors = malloc(8*8)};

                // Add the dot to active dots and change the respective screen position
                num_of_active_dots += 1;
                active_nodes[num_of_active_dots-1] = &dot;
                terminal -> screen[dot.posY][dot.posX] = '*';
            }
        }
    }
}

void init_sim(terminal_struct* terminal)
{
    while (1)
    {
        if (check_cells(terminal) == 1)
        {
            printf("\e[1;1H\e[2J");
            return;
        }
    }
}

int check_cells(terminal_struct* terminal)
{
    for (int i = 0; i < num_of_active_dots; i++)
    {
        // For each node check if we are out of bounds
        if (active_nodes[i] -> posY > terminal -> terminal_params -> ws_row ||
            active_nodes[i] -> posX > terminal -> terminal_params -> ws_col)
        {
            return 1;
        }

        // Then we clear the active dots from the previous frame
        terminal -> screen[active_nodes[i] -> posY][active_nodes[i] -> posX] = ' ';


        // TODO: Figure out how to check current dots and create new array
    }

    return 0;
}
