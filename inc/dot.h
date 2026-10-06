#pragma once
#include <stdlib.h>


// Total size 4(int) + 4(int) + 8*8(pointer array)
typedef struct
{
  int posX;
  int posY;
  // Pointers are 8 bytes size, and we can have 8 neighbours
  void* neighbours;
} dot_t;
// Used to access the "neighbours" array
typedef dot_t* dot_ptr;

void dot_init(dot_ptr dot, int posX, int posY);