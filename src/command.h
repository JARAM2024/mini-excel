#ifndef __COMMAND_H
#define __COMMAND_H

#include "common.h"
#include "table.h"
#include "method.h"

#if defined(_MSC_VER) || defined(_WIN32)

#else
#include "compile.h"
#endif

struct command_list {
  size_t length;
  size_t capacity;
  struct command* data;
};

struct command {
  char* name;
  enum TABLE_RESULT (* function)(struct table* , struct method_parameter* );
  void* handle;
};

enum TABLE_RESULT run_command(struct table* table, int* );
enum TABLE_RESULT find_command(struct command* , char const* const );
void init_commands();
void add_command(void* handle, char const* function_name);

extern struct command_list command_list;

#endif
