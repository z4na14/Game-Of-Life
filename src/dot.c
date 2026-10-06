#include "dot.h"


int num_active_dots;
dot_t active_dots[100];


/* Function: matrix_init
 * ---------------------
 * Initialize the matrix of dots using the pattern inputted by the user
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

                // Add the dot to active dots and change the respective screen position
                num_active_dots++;
                active_dots[num_active_dots-1] = dot;
                terminal -> screen[dot.posY][dot.posX] = '*';
            }
        }
    }
}

// TODO: Comment functions

void simulate_behavior(terminal_struct* terminal)
{
    while (1)
    {
        int num_new_dots = 0;
        dot_t new_dots[100];
        // For all active dots, we check for deletions or creations and then we update the original array
        for (int i = 0; i < num_active_dots; i++)
        {
            // Then we clear the active dots from the previous frame
            terminal -> screen[active_dots[i].posY][active_dots[i].posX] = ' ';
            check_neighbors(new_dots, &num_new_dots, active_dots[i].posY, active_dots[i].posX, 1);
        }

        // If any of the new nodes gets outside of bounds, we end the program
        for (int i = 0; i < num_new_dots; i++)
        {
            if (new_dots[i].posY >= terminal -> terminal_params -> ws_row ||
                new_dots[i].posX >= terminal -> terminal_params -> ws_col)
            {
                return;
            }

            // All new dots will be copied to the global array
            active_dots[i] = new_dots[i];
            // And the screen array will be updated
            terminal -> screen[new_dots[i].posY][new_dots[i].posX] = '*';
        }

        // Finally print the new chars
        update_terminal(print_chars);

        // TODO: Set timeout function so the updates are clearly seen on screen
    }
}

// Return the number of neighbours the position has
int check_neighbors(dot_t new_dots[], int *num_new_dots, int posY, int posX, int is_dot)
{
    int neighbors = 0;
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            // Check if we are in the middle pos
            if (i == 0 && j == 0)
            {
                continue;
            }

            // just check for every node in the active ones and sum the count
            for (int index = 0; index < num_active_dots; index++)
            {
                if (active_dots[index].posY == posY + i && active_dots[index].posX == posX + j)
                {
                    neighbors++;
                }
            }

            // We need to check if each neighbour connect with another dot
            if (is_dot == 1)
            {
                if (check_neighbors(new_dots, num_new_dots, posY + i, posX + j, 0) == 3)
                {
                    int found = 0;
                    for (int z = 0; z < *num_new_dots; z++)
                    {
                        if (new_dots[z].posY == posY + i && new_dots[z].posX == posX + j)
                        {
                            found = 1;
                            break;
                        }
                        z++;
                    }

                    if (found == 0)
                    {
                        dot_t new_dot = {.posY = i + posY, .posX = j + posX};
                        *num_new_dots++;
                        new_dots[*num_new_dots-1] = new_dot;
                    }
                }
            }
        }
    }

    if (neighbors == 2 || neighbors == 3 || is_dot == 1)
    {
        // Add new dot to array
        dot_t new_dot = {.posY = posY, .posX = posX};
        *num_new_dots++;
        new_dots[*num_new_dots-1] = new_dot;
    }

    return neighbors;
}
