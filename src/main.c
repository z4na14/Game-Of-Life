#include "dot.h"
#include <string.h>


int main(int argc, char *argv[])
{
    // Create terminal instance and set all screen characters clear
    init_terminal();
    update_terminal(set_clear_chars);


    // Temporal, to check everything works
    char *pattern[] = {" * ",
                       "  *",
                       "***",};

    matrix_init(pattern, strlen(pattern[0]),
    sizeof(pattern)/sizeof(pattern[0]), get_terminal_ptr());

    simulate_behavior(get_terminal_ptr());

    return 0;
}