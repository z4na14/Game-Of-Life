#pragma once
#include "console.h"


// Total size 4(int) + 4(int) + 8*8(pointer array)
typedef struct
{
  int posX;
  int posY;
  // Pointers are 8 bytes size, and we can have 8 neighbours
  //void *neighbours[8];
} dot_t;
// Used to access the "neighbours" array
typedef dot_t* dot_ptr;

void matrix_init(char *pattern[], int pattern_size_X, int pattern_size_Y, terminal_struct* terminal);
void init_sim(terminal_struct* terminal);
int check_cells(terminal_struct* terminal);