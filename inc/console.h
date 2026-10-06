#include <stdio.h>
#include <sys/ioctl.h>


typedef struct winsize* winsize_t;
int update_console(void);
struct winsize* create_console(void);