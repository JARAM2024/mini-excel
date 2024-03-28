#ifndef __TABLE_H
#define __TABLE_H

#include "list.h"

enum TABLE_RESULT {
  TABLE_RESULT_OK,
  TABLE_RESULT_FAIL,
  TABLE_ERR_INPUT_IS_NULL,
  TABLE_ERR_TABLE_IS_NULL,
  TABLE_ERR_DATA_IS_NULL,
  TABLE_ERR_OUTPUT_PARAMETER_NULL,
  TABLE_ERR_ELEMENTS_PARAMETER_INEFFICIENT,
  TABLE_ERR_INVALID_INDEX_ROW,
  TABLE_ERR_INVALID_INDEX_COL,
  TABLE_ERR_COMMAND_NOT_FOUND,
  TABLE_ERR_NOT_IMPLEMENTED,
  TABLE_RESULT_LEGNTH,
};

extern char const* table_result_messages[TABLE_RESULT_LEGNTH];

struct table {
  size_t n_rows;
  size_t n_cols;

  struct list** data;
};

enum TABLE_RESULT table_make(struct table* table, size_t n_rows, size_t n_cols);
enum TABLE_RESULT table_clean(struct table* table);
enum TABLE_RESULT table_get_data(struct table* table, size_t i_row, size_t i_col, int* output);
enum TABLE_RESULT table_set_data(struct table* table, size_t i_row, size_t i_col, int input);
enum TABLE_RESULT table_render(struct table* table);
enum TABLE_RESULT table_add_row(struct table* table, int* elements);
enum TABLE_RESULT table_add_col(struct table* table, int* elements);

#endif
