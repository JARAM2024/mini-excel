#include "common.h"

#if defined(_MSC_VER) || defined(_WIN32)

void clean_terminal() {
  system("cls");
}

#elif __APPLE__

void clean_terminal() {
  fprintf(stderr, "\x1b[2J\x1b[H");
}

#else

void clean_terminal() {
  fprintf(stderr, "\x1b[2J\x1b[H");
}

#endif
