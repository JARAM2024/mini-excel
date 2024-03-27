#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>

#if defined _MSC_VER
#include <windows.h>
#include <io.h>
void clean_terminal() {
  system("cls");
}
#undef max
#undef min
#define STDIN_FILENO _fileno(stdin)
#define STDOUT_FILENO _fileno(stdout)
#define STDERR_FILENO _fileno(stderr)
#elif __APPLE__
#include <unistd.h>
#include <dlfcn.h>

void clean_terminal() {
  printf("\033[2J\033[3J\033[H");
}
#else
#include <unistd.h>
#include <dlfcn.h>

void clean_terminal() {
  printf("\033[2J\033[3J\033[H");
}
#endif

#endif
