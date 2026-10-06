#include "dot.h"


int num_active_dots;
dot_ptr active_dots[100];


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

                // Add the dot to active dots and change the respective screen position
                num_active_dots++;
                active_dots[num_active_dots-1] = &dot;
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
        dot_ptr new_dots[100];
        // For all active nodes, we check for deletions or creations and then we update the original array
        for (int i = 0; i < num_active_dots; i++)
        {
            // Then we clear the active dots from the previous frame
            terminal -> screen[active_dots[i] -> posY][active_dots[i] -> posX] = ' ';
            check_neighbors(new_dots, &num_new_dots, active_dots[i] -> posY, active_dots[i] -> posX, 1);
        }

        // If any of the new nodes gets outside of bounds, we end the program
        for (int i = 0; i < num_new_dots; i++)
        {
            if (new_dots[i] -> posY > terminal -> terminal_params -> ws_row ||
                new_dots[i] -> posX > terminal -> terminal_params -> ws_col)
            {
                return;
            }

            // All new dots will be copied to the global array
            // TODO: update the terminal screen with the new nodes

        }

        free(new_dots);
        // Finnaly print the new chars
        update_terminal(print_chars);

        // TODO: Set timeout function so the updates are clearly seen on screen
    }
}

// Return the number of neighbours the position has
int check_neighbors(dot_ptr new_nodes[], int *num_new_nodes, int posY, int posX, int is_dot)
{
    int neighbors = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // Check if we are in the middle pos
            if (i == posY && j == posX)
            {
                continue;
            }

            // TODO: Check for the neighbours
            // just check for every node in the active ones and sum the count

            // We need to check if each neighbour connect with another dot
            if (is_dot == 1)
            {
                if (check_neighbors(new_nodes, num_new_nodes, i, j, 0) == 3)
                {
                    int found = 0;
                    int z = 0;
                    while (new_nodes[z] != NULL)
                    {
                        if (new_nodes[z] -> posY == posY && new_nodes[z] -> posX == posX)
                        {
                            found = 1;
                            break;
                        }
                        z++;
                    }

                    if (found == 0)
                    {
                        dot_t new_dot = {.posY = i, .posX = j};
                        *num_new_nodes++;
                        new_nodes[*num_new_nodes-1] = &new_dot;
                    }
                }
            }
        }
    }

    return neighbors;
}
