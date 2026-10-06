#include <stdlib.h>
#include "console.h"
#include "dot.h"


int main(int argc, char *argv[]) {
    // Get the struct with the size of the console
    winsize_t terminal_params;
    ioctl(0, TIOCGWINSZ, &terminal_params);

    // Define the structure of the terminal
    terminal_struct terminal = {.screen = malloc(terminal_params.ws_row * sizeof(char*)),
                                .midX = terminal_params.ws_col / 2,
                                .midY = terminal_params.ws_row / 2,
                                .terminal_params = &terminal_params};
    terminal_struct* terminal_ptr = &terminal;

    for (int i = 0; i < terminal_params.ws_row; i++) {
        terminal_ptr -> screen[i] = malloc(terminal_params.ws_col * sizeof(char));
    }

    // Try to print the characters to fill the terminal
    init_terminal(terminal_ptr);
    return 0;
}