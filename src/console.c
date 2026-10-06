#include "console.h"


winsize_t create_console(void)
{
    struct winsize *terminal_size;
    ioctl(0, TIOCGWINSZ, terminal_size);

    typedef struct
    {
        char screen[terminal_size -> ws_row][terminal_size -> ws_col];
         // TODO: define middle character
        int midX;
        int midY;
    } terminal;

    return terminal_size;
}
