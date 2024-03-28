#include "compile.h"

#if defined(_MSC_VER) || defined(_WIN32)

#else
char const* const headers = HEADER(common.h) HEADER(table.h) HEADER(method.h);

enum COMPILE_RESULT compile(char const* const code, void** lib_handle) {
  enum COMPILE_RESULT result = COMPILE_RESULT_OK;
  int current_time = time(NULL);
  char* buffer = NULL;
  asprintf(&buffer, "tmp-%d.o", current_time);

  if (code == NULL) return COMPILE_RESULT_FAIL;
  if (buffer == NULL) return COMPILE_RESULT_FAIL;

  int inputfd[2];
  pipe(inputfd);

  pid_t pid = fork();
  if (pid == 0) {
    dup2(inputfd[0], 0);

    close(inputfd[0]);
    close(inputfd[1]);

    char* const compiler_path = CMAKE_C_COMPILER;
    if (compiler_path == NULL) return COMPILE_ERR_COMPILER_NOT_FOUND;
    char* const argv[] = {compiler_path, "-xc", "-", "-shared", "-o", buffer, NULL};

    execv(compiler_path, argv);
    result = COMPILE_ERR_COMPILER_NOT_FOUND;
    goto CLEANUP;
  } else {
    write(inputfd[1], headers, strlen(headers));
    write(inputfd[1], code, strlen(code));
    char output[14096];
    size_t output_len = 0;
    int n_read = 0;
    
    close(inputfd[0]);
    close(inputfd[1]);
    
    waitpid(pid, NULL, 0);
  }
  
  void* handle = dlopen(buffer, RTLD_LOCAL | RTLD_NOW);
  if (handle == NULL) {
    result = COMPILE_ERR_FAIL_TO_LOAD_PLUGIN;
    goto CLEANUP;
  }

  *lib_handle = handle;

CLEANUP:
  remove(buffer);
  free(buffer);
  return result;
}
#endif