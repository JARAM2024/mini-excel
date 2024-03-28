#include "common.h"

#if defined(_MSC_VER) || defined(_WIN32)

void clean_terminal() {
  system("cls");
}

#elif __APPLE__

void clean_terminal() {
  printf("\033[2J\033[3J\033[H");
}

#else

void clean_terminal() {
  printf("\033[2J\033[3J\033[H");
}

#endif
