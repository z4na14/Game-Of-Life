#include "dot.h"
#include <string.h>


int main(int argc, char *argv[])
{
    // Create terminal instance and set all screen characters clear
    init_terminal();
    update_terminal(set_clear_chars);

    // Create a pattenr struct and update it with the user input
    pattern_t pattern;
    get_user_pattern(&pattern);

    // Update the information of the screen with the user pattern
    // and begin the simulation
    matrix_init(pattern.pattern, pattern.cols,
        pattern.rows, get_terminal_ptr());
    update_terminal(print_chars);
    simulate_behavior(get_terminal_ptr());

    return 0;
}