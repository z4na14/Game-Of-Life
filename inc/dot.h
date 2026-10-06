#pragma once
#include "console.h"


typedef struct {
  int posX;
  int posY;
  // Used for debugging purposes
  int neighbors;
} dot_t;

void matrix_init(char *pattern[], int pattern_size_X, int pattern_size_Y, terminal_struct* terminal);
void simulate_behavior(terminal_struct* terminal);
int check_neighbors(dot_t new_dots[], int *num_new_dots, int posY, int posX, int is_dot);
int dot_exists(dot_t dots_arr[], int *num_dots, int posY, int posX);