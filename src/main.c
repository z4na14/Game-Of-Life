#include "dot.h"
#include "console.h"


int main(int argc, char *argv[]) {
  winsize_t windowsize = create_console();
  printf("%d\n", windowsize -> ws_col);
  return 0;
}