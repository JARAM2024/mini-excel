#include "command.h"

struct command_list command_list = { 0 };

enum TABLE_RESULT run_command(struct table* table, int* result) {
  char buffer[4096] = { 0 };
  int n_size = 0;
  int n_read = 0;

  while ((n_read = read(STDIN_FILENO, buffer + n_size, 4095 - n_size))) {
    n_size += n_read;
    if (n_size < 1) return TABLE_ERR_INPUT_IS_NULL;
    if (buffer[n_size - 1] == '\n') {
      n_size -= 1;
    }
    if (buffer[n_size - 1] == '\\') {
      n_size -= 1;
      continue;
    }

    buffer[n_size] = 0;
    break;
  }

  if (n_size == 0) {
    exit(0);
  }

  size_t n_token = 0;
  struct method_parameter* parameter = NULL;

  char const* command_name = NULL;
  struct command command = { 0 };
  int is_new_command_method = 0;
  char const* new_command_name = NULL;
  char const* new_command_source = NULL;

  char const* tok = strtok(buffer, " ");
  do {
    switch (n_token) {
      case 0:
        if (strcmp(tok, "new_command") == 0) {
          is_new_command_method = 1;
        } else if (strcmp(tok, "list_command") == 0) {
          for (int i = 0; i < command_list.length; ++i) {
            printf("Command: %s exist\n", command_list.data[i].name);
          }
          
          return run_command(table, result);
        }
        command_name = tok;
        break;
      case 1:
        if (is_new_command_method) {
          new_command_name = tok;
          char const* tmp = tok + strlen(tok);
          new_command_source = tmp + 1;
          goto WHILE_OUT;
        }
      case 2: {
        enum PARAMETER_TYPE parameter_type = get_parameter_type(tok);
        if (parameter_type == PARAMETER_NULL_TYPE)
          goto WHILE_OUT;
        parameter = new_parameter(parameter_type);
        char const* const tmp = tok + strlen(tok);
        char const* const parameter_string = tmp + 1;
        struct_parameter(parameter, parameter_string);
        goto WHILE_OUT;
      }
      default:
        break;
    }

    ++n_token;
  } while ((tok = strtok(NULL, " ")));
WHILE_OUT:

  if (is_new_command_method) {
#if defined(_MSC_VER) || defined(_WIN32)
    fprintf(stderr, "new_comamnd is not available for windows now.\n");
    return TABLE_ERR_NOT_IMPLEMENTED;
#else
    if (new_command_name == NULL || new_command_source == NULL) {
      fprintf(stderr, "new_command_name: %s, new_command_source: %s\n", new_command_name, new_command_source);
      return TABLE_RESULT_FAIL;
    }

    void* lib_handle = NULL;
    enum COMPILE_RESULT compile_result = compile(new_command_source, &lib_handle);
    if (compile_result != TABLE_RESULT_OK || lib_handle == NULL) {
      fprintf(stderr, "compile_result: %d, lib_handle: %p\n", compile_result, lib_handle);
      return TABLE_RESULT_FAIL;
    }

    add_command(lib_handle, new_command_name);
    return run_command(table, result);
#endif
  }

  int command_result = find_command(&command, command_name);
  if (command_result != TABLE_RESULT_OK) return command_result;

  command_result = TABLE_ERR_ELEMENTS_PARAMETER_INEFFICIENT;
  if (parameter) {
    parameter->result = result;
    command_result = command.function(table, parameter);
    clean_parameter(parameter);
    free(parameter);
  }
  if (command_result != TABLE_RESULT_OK) return command_result;

  return TABLE_RESULT_OK;
}


enum TABLE_RESULT find_command(struct command* command, char const* const name) {
  for (int i = 0; i < command_list.length; ++i) {
    if (strcmp(command_list.data[i].name, name) == 0) {
      *command = command_list.data[i];
      return TABLE_RESULT_OK;
    }
  }
  return TABLE_ERR_COMMAND_NOT_FOUND;
}

void init_commands() {
  command_list.length = 9;
  command_list.capacity = 16;
  command_list.data = (struct command* )malloc(sizeof(struct command) * command_list.capacity);
  int index = 0;

#define ADD_COMMAND(X) \
  command_list.data[index++] = (struct command) { \
    .name = #X , \
    .function = X , \
  };

  ADD_COMMAND(get);
  ADD_COMMAND(set);
  ADD_COMMAND(sum);
  ADD_COMMAND(average);
  ADD_COMMAND(max);
  ADD_COMMAND(min);
  ADD_COMMAND(append);
  ADD_COMMAND(delete);
  ADD_COMMAND(not_implemented);

}

#if defined(_MSC_VER) || defined(_WIN32)

#else
void add_command(void* handle, char const* function_name) {
  if (handle == NULL || function_name == NULL) return;

  enum TABLE_RESULT (* function)(struct table* , struct method_parameter* ) = 
    (enum TABLE_RESULT (* )(struct table*, struct method_parameter* ))dlsym(handle, function_name);
  if (function == NULL) return;
  
  if (command_list.length + 1 >= command_list.capacity) {
    command_list.capacity *= 2;
    void* new = realloc(command_list.data, sizeof(struct command) * command_list.capacity);
    if (new == NULL) return;
    command_list.data = (struct command* )new;
  }

  command_list.data[command_list.length] = (struct command) {
    .name = strdup(function_name),
    .function = function,
    .handle = handle,
  };
  
  ++command_list.length;
}
#endif
