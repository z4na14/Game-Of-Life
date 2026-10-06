#pragma once
// All C libraries used will be defined here
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
// console.h (console.c) -> dot.h (dot.c) -> main.c


typedef struct winsize winsize_t;
typedef struct {
    char** screen;
    int midX;
    int midY;
    winsize_t* terminal_params;
} terminal_struct;

typedef struct {
    int rows;
    int cols;
    char** pattern;
} pattern_t;

terminal_struct* get_terminal_ptr();

typedef void update_console_funcs(int, int);
void init_terminal();
void update_terminal(update_console_funcs function);
void print_chars(int i, int j);
void set_clear_chars(int i, int j);

void get_user_pattern(pattern_t *pattern);
