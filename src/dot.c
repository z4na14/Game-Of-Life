#include "dot.h"


int num_active_dots;
dot_t active_dots[500];


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

void matrix_init(char *pattern[], int pattern_size_X, int pattern_size_Y, terminal_struct* terminal) {
    // Define the middle part for the terminal and the pattern to do the calculations
    int midX = terminal -> midX, midY = terminal -> midY;
    int mid_patternX = pattern_size_X / 2;
    int mid_patternY = pattern_size_Y / 2;

    for (int i = 0; i < pattern_size_Y; i++) {
        int j = 0;
        while(pattern[i][j] != '\0') {
            if (pattern[i][j] == '*' || pattern[i][j] == '.' || pattern[i][j] == 'x') {
                // Create the new dot instance
                dot_t dot = {.posX = (j < mid_patternX) ? midX - (mid_patternX - j) : midX + (j - mid_patternX),
                             .posY = (i < mid_patternY) ? midY - (mid_patternY - i) : midY + (i - mid_patternY),
                              .neighbors = 0};

                // Add the dot to active dots and change the respective screen position
                num_active_dots++;
                active_dots[num_active_dots-1] = dot;
                terminal -> screen[dot.posY][dot.posX] = '*';
            }

            j++;
        }
    }
}

// TODO: Comment functions

void simulate_behavior(terminal_struct* terminal) {
    sleep(2);
    while (1) {
        int num_new_dots = 0;
        dot_t new_dots[500];
        // For all active dots, we check for deletions or creations and then we update the original array
        for (int i = 0; i < num_active_dots; i++) {
            // Then we clear the active dots from the previous frame
            terminal->screen[active_dots[i].posY][active_dots[i].posX] = ' ';
            check_neighbors(new_dots, &num_new_dots, active_dots[i].posY, active_dots[i].posX, 1);
        }

        // If any of the new nodes gets outside of bounds, we end the program
        for (int i = 0; i < num_new_dots; i++) {
            if (new_dots[i].posY >= terminal -> terminal_params -> ws_row ||
                new_dots[i].posX >= terminal -> terminal_params -> ws_col ||
                new_dots[i].posY < 0 || new_dots[i].posX < 0) {
                return;
            }

            // All new dots will be copied to the global array
            active_dots[i] = new_dots[i];
            // And the screen array will be updated
            terminal -> screen[new_dots[i].posY][new_dots[i].posX] = '*';
        }
        num_active_dots = num_new_dots;
        num_new_dots = 0;
        // Finally print the new chars
        update_terminal(print_chars);
        sleep(1);
    }
}

// Return the number of neighbours the position has
int check_neighbors(dot_t new_dots[], int *num_new_dots, int posY, int posX, int is_dot) {
    int neighbors = 0;
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            // Check if we are in the middle pos
            if (i == 0 && j == 0) {
                continue;
            }

            // just check for every node in the active ones and sum the count
            for (int index = 0; index < num_active_dots; index++) {
                if (active_dots[index].posY == posY + i && active_dots[index].posX == posX + j) {
                    neighbors++;
                }
            }

            // We need to check if each neighbour connect with another dot
            if (is_dot == 1 && check_neighbors(new_dots, num_new_dots, posY + i, posX + j, 0) == 3) {
                if (dot_exists(new_dots, num_new_dots, i + posY, j + posX) == 0 && *num_new_dots < 500) {
                    dot_t new_dot = {.posY = i + posY, .posX = j + posX, .neighbors = 3};
                    (*num_new_dots)++;
                    new_dots[(*num_new_dots)-1] = new_dot;
                }
            }
        }
    }

    if (is_dot == 1 && (neighbors == 2 || neighbors == 3)) {
        if (dot_exists(new_dots, num_new_dots, posY, posX) == 0 && *num_new_dots < 500) { // Ensures no overflow
            // Add new dot to array
            dot_t new_dot = {.posY = posY, .posX = posX, .neighbors = neighbors};
            (*num_new_dots)++;
            new_dots[(*num_new_dots)-1] = new_dot;
        }
    }
    return neighbors;
}

int dot_exists(dot_t dots_arr[], int *num_dots, int posY, int posX) {
    for (int i = 0; i < *num_dots; i++) {
        if (dots_arr[i].posY == posY && dots_arr[i].posX == posX) {
            return 1;
        }
    }
    return 0;
}
