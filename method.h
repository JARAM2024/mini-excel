#ifndef __METHOD_H
#define __METHOD_H

#include "common.h"
#include "table.h"

enum PARAMETER_TYPE {
  PARAMETER_NULL_TYPE,
  PARAMETER_POINT_TYPE,
  PARAMETER_BOX_TYPE,
  PARAMETER_LIST_TYPE,
  PARAMETER_TYPE_LENGTH,
};

char const* parameter_type_string[PARAMETER_TYPE_LENGTH] = {
  [PARAMETER_NULL_TYPE] = "NULL",
  [PARAMETER_POINT_TYPE] = "point",
  [PARAMETER_BOX_TYPE] = "box",
  [PARAMETER_LIST_TYPE] = "list",
};

struct method_parameter {
  enum PARAMETER_TYPE type;
  int* result;
};

struct point_paramter {
  enum PARAMETER_TYPE type;
  int* result;
  size_t i_row;
  size_t i_col;
};

struct box_parameter {
  enum PARAMETER_TYPE type;
  int* result;
  size_t i_row;
  size_t i_col;
  size_t n_rows;
  size_t n_cols;
};

struct list_parameter {
  enum PARAMETER_TYPE type;
  int* result;
  size_t i_row;
  size_t i_col;
  int* list;
};

typedef enum TABLE_RESULT (* method)(struct table* table, struct method_parameter* parameter);
#define TABLE_FUNCTION(X, Y) enum TABLE_RESULT X (struct table* table, struct method_parameter* parameter) { \
  if (table == NULL) return TABLE_ERR_TABLE_IS_NULL; \
  if (table->data == NULL) return TABLE_ERR_DATA_IS_NULL; \
  Y; return TABLE_ERR_NOT_IMPLEMENTED; }

// Input: table (struct parameter* ), 
//        parameter (struct method_parameter* )
// 
// Output: parameter->result (int *)

// Set data to specific range
TABLE_FUNCTION(set, {

  // Implement code here!! 

  return TABLE_RESULT_OK;
})

// Get data from specific range
TABLE_FUNCTION(get, {

  // Implement code here!! 

  return TABLE_RESULT_OK;
})

// Get sum of data from specific range
TABLE_FUNCTION(sum, {

  // Implement code here!! 

  return TABLE_RESULT_OK;
})

// Get average of data from specific range
TABLE_FUNCTION(average, {

  // Implement code here!! 

  return TABLE_RESULT_OK;
})

// Get maximum of data from specific range
TABLE_FUNCTION(max, {

  // Implement code here!! 

  return TABLE_RESULT_OK;
})

// Get minimum of data from specific range
TABLE_FUNCTION(min, {

  // Implement code here!! 

  return TABLE_RESULT_OK;
})

// Append new rows or columns for specific range
TABLE_FUNCTION(append, {

  // Implement code here!! 

  return TABLE_RESULT_OK;
})

// Delete new rows or columns fror specific range
TABLE_FUNCTION(delete, {

  // Implement code here!! 

  return TABLE_RESULT_OK;
})

TABLE_FUNCTION(not_implemented, )

enum PARAMETER_TYPE get_parameter_type(char const* const type_str) {
  for (int i = 0; i < PARAMETER_TYPE_LENGTH; ++i) {
    if (strcmp(parameter_type_string[i], type_str) == 0) return (enum PARAMETER_TYPE)i;
  }
  
  return PARAMETER_NULL_TYPE;
}

#endif
