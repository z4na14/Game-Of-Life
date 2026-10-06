#pragma once
#include "console.h"


typedef struct
{
  int posX;
  int posY;
} dot_t;
// Used to access the "neighbours" array
typedef dot_t* dot_ptr;

void matrix_init(char *pattern[], int pattern_size_X, int pattern_size_Y, terminal_struct* terminal);
void simulate_behavior(terminal_struct* terminal);
int check_neighbors(dot_ptr new_nodes[], int *num_new_nodes, int posY, int posX, int is_dot);