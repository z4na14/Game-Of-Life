#include "dot.h"
#include <string.h>
// console.h -> dot.h -> main.c


int main(int argc, char *argv[])
{
    // Create terminal instance and set all screen characters clear
    init_terminal();
    update_terminal(set_clear_chars);
    update_terminal(print_chars);


    // Temporal, to check everything works
    char *pattern[] = {" * ",
                       "  *",
                       "***",};
    matrix_init(pattern, strlen(pattern[0]),
    sizeof(pattern)/sizeof(pattern[0]), get_terminal_ptr());
    update_terminal(print_chars);

    return 0;
}