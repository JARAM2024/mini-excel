#include "common.h"
#include "table.h"
#include "command.h"

void print_err(enum TABLE_RESULT result) {
  fprintf(stderr, "Err: %s\n", table_result_messages[result]);
  fgetc(stdin);
  clean_terminal();
}

int main(int argc, char* argv[]) {
  init_commands();
  clean_terminal();

  struct table my_table = { 0 };

  table_make(&my_table, 3, 6);

  while(1) {
    int result = 0;
    int render_result = table_render(&my_table);
    if (render_result != TABLE_RESULT_OK) {
      print_err(render_result);
      continue;
    }
    
    int command_result = run_command(&my_table, &result);
    if (command_result != TABLE_RESULT_OK) {
      print_err(command_result);
      continue;
    }

    printf("Result: %d\n", result);
    printf("To continue... press ENTER!");

    fgetc(stdin);

    clean_terminal();
  }

  return 0;
}
