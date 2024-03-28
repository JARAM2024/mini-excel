#ifndef __COMPILE_H
#define __COMPILE_H

#include "common.h"

enum COMPILE_RESULT {
  COMPILE_RESULT_OK,
  COMPILE_RESULT_FAIL,
  COMPILE_ERR_COMPILER_NOT_FOUND,
  COMPILE_ERR_FAIL_TO_LOAD_PLUGIN,
};

#define HEADER(X) "#include \""#X"\"\n"

extern char const* const headers;

enum COMPILE_RESULT compile(char const* const code, void** lib_handle);

#endif
