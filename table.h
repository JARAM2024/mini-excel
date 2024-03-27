#ifndef __TABLE_H
#define __TABLE_H

#include "common.h"
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
  TABLE_RESULT_LEGNTH,
};

char* table_result_messages[TABLE_RESULT_LEGNTH] = {
  [TABLE_RESULT_OK] = "This table method is ok",
  [TABLE_RESULT_FAIL] = "This table method is failed",
  [TABLE_ERR_INPUT_IS_NULL] = "There is no input",
  [TABLE_ERR_TABLE_IS_NULL] = "This table pointer is null",
  [TABLE_ERR_DATA_IS_NULL] = "This table's data pointer is null",
  [TABLE_ERR_OUTPUT_PARAMETER_NULL] = "Output pointer is null in parameters",
  [TABLE_ERR_ELEMENTS_PARAMETER_INEFFICIENT] = "Elements is not efficient in parameters",
  [TABLE_ERR_INVALID_INDEX_ROW] = "Index row is too big for this table",
  [TABLE_ERR_INVALID_INDEX_COL] = "Index col is too big for this table",
  [TABLE_ERR_COMMAND_NOT_FOUND] = "Such command does not exist",
};

struct table {
  size_t n_rows;
  size_t n_cols;

  struct list** data;
};

enum TABLE_RESULT table_make(struct table* table, size_t n_rows, size_t n_cols) {
  if (table == NULL) return TABLE_ERR_TABLE_IS_NULL;

  table->n_rows = n_rows;
  table->n_cols = n_cols;
  table->data = (struct list** )malloc(sizeof(struct list* ) * n_rows);
  for (int i = 0; i < n_rows; ++i) {
    table->data[i] = NULL;
    list_make(&table->data[i], n_cols);
  }

  return TABLE_RESULT_OK;
}

enum TABLE_RESULT table_clean(struct table* table) {
  if (table == NULL) return TABLE_ERR_TABLE_IS_NULL;

  for (int i = 0;i < table->n_rows; ++i) {
    free(table->data[i]);
  }
  
  free(table->data);
  table->data = NULL;

  return TABLE_RESULT_OK;
}

enum TABLE_RESULT table_get_data(struct table* table, size_t i_row, size_t i_col, int* output) {
  if (table == NULL) return TABLE_ERR_TABLE_IS_NULL;
  if (output == NULL) return TABLE_ERR_OUTPUT_PARAMETER_NULL;
  if (table->n_rows <= i_row) return TABLE_ERR_INVALID_INDEX_ROW;
  if (table->n_cols <= i_col) return TABLE_ERR_INVALID_INDEX_COL;

  *output = list_get(table->data[i_row], i_col);

  return TABLE_RESULT_OK;
}

enum TABLE_RESULT table_set_data(struct table* table, size_t i_row, size_t i_col, int input) {
  if (table == NULL) return TABLE_ERR_TABLE_IS_NULL;
  if (table->n_rows <= i_row) return TABLE_ERR_INVALID_INDEX_ROW;
  if (table->n_cols <= i_col) return TABLE_ERR_INVALID_INDEX_COL;

  list_set(table->data[i_row], i_col, input);

  return TABLE_RESULT_OK;
}

enum TABLE_RESULT table_render(struct table* table) {
  if (table == NULL) return TABLE_ERR_TABLE_IS_NULL;
  
  printf("|----|");
  for (int i = 0; i < table->n_cols; ++i) printf("|%2dth|", i);
  printf("\n");
  
  for (int i = 0; i < table->n_rows; ++i) {
    printf("|%2dth|", i);
    
    for (int j = 0; j < table->n_cols; ++j) {
      
      int c = 0;
      if (table_get_data(table, i, j, &c) != TABLE_RESULT_OK)
        return TABLE_RESULT_FAIL;

      printf("|%4d|", c);

    }

    printf("\n");
  }

  for (int i = 0; i < table->n_cols + 1; ++i) printf("|----|");
  printf("\n");

  return TABLE_RESULT_OK;
}

enum TABLE_RESULT table_add_row(struct table* table, int* elements) {
  if (table == NULL) return TABLE_ERR_TABLE_IS_NULL;

  int* row = (int* )malloc(sizeof(int) * table->n_cols);


  return TABLE_RESULT_OK;
};

#endif
