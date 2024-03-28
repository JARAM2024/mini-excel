#ifndef __METHOD_H
#define __METHOD_H

#include "common.h"
#include "table.h"

enum PARAMETER_TYPE {
  PARAMETER_POINT_TYPE,
  PARAMETER_BOX_TYPE,
  PARAMETER_LIST_TYPE,
  PARAMETER_TYPE_LENGTH,
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

TABLE_FUNCTION(set, {

  // Implement code here!! 

  return TABLE_RESULT_OK;
})

TABLE_FUNCTION(get, {

  // Implement code here!! 

  return TABLE_RESULT_OK;
})

TABLE_FUNCTION(sum, {

  // Implement code here!! 

  return TABLE_RESULT_OK;
})

TABLE_FUNCTION(average, {

  // Implement code here!! 

  return TABLE_RESULT_OK;
})

TABLE_FUNCTION(max, {

  // Implement code here!! 

  return TABLE_RESULT_OK;
})

TABLE_FUNCTION(min, {

  // Implement code here!! 

  return TABLE_RESULT_OK;
})

TABLE_FUNCTION(append, {

  // Implement code here!! 

  return TABLE_RESULT_OK;
})

TABLE_FUNCTION(delete, {

  // Implement code here!! 

  return TABLE_RESULT_OK;
})

TABLE_FUNCTION(notimplemented, )

#endif
