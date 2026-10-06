#include "console.h"


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

void init_terminal() {
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

void get_user_pattern(pattern_t *pattern) {
    // Allocate memory for the rows of the pattern array
    pattern->pattern = malloc(terminal_params.ws_row * sizeof(char*));
    if (pattern->pattern == NULL) {
        perror("Failed to allocate memory for pattern rows");
        exit(1);
    }

    int cols = 0;
    int rows = 0;

    while (1) {
        if (rows >= terminal_params.ws_row) {
            break;  // Avoid going beyond allocated rows
        }

        // Allocate memory for each row
        pattern->pattern[rows] = malloc(terminal_params.ws_col * sizeof(char));
        if (pattern->pattern[rows] == NULL) {
            perror("Failed to allocate memory for pattern columns");
            exit(1);
        }

        // Read the user input into the current row
        if (fgets(pattern->pattern[rows], terminal_params.ws_col, stdin) == NULL) {
            free(pattern->pattern[rows]); // Free the last allocated row on EOF
            break;  // Stop on EOF or input error
        }

        int curr_length = strlen(pattern->pattern[rows]);

        // If the line is empty (only contains newline), end input collection
        if (curr_length <= 1) {
            free(pattern->pattern[rows]); // Free the last row that won't be used
            break;
        }

        // Update the maximum column width
        if (cols < curr_length) {
            cols = curr_length;
        }

        // Reallocate the current row to fit exactly the input length + null terminator
        char *temp = realloc(pattern->pattern[rows], (curr_length + 1) * sizeof(char));
        if (temp == NULL) {
            perror("Failed to realloc");
            exit(1);
        }
        pattern->pattern[rows] = temp;

        rows++;
    }

    // Store the final rows and columns count
    pattern->rows = rows;
    pattern->cols = cols;

    // Resize pattern->pattern to save memory for unused rows
    char **temp = realloc(pattern->pattern, rows * sizeof(char*));
    if (temp != NULL) {
        pattern->pattern = temp;
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

void update_terminal(update_console_funcs function) {
    printf("\e[1;1H\e[2J");
    for (int i = 0; i < terminal_ptr -> terminal_params -> ws_row; i++) {
        for (int j = 0; j < terminal_ptr -> terminal_params -> ws_col; j++) {
            function(i, j);
        }
        printf("\n");
    }

    printf("\n");
}

void set_clear_chars(int i, int j) {
    terminal_ptr -> screen[i][j] = ' ';
}

void print_chars(int i, int j) {
    if (terminal_ptr -> screen[i][j] == '*') {
        printf("\033[48;2;255;255;255m \033[0m");
    }
    else {
        printf(" ");
    }
}
