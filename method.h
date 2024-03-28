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

struct point_parameter {
  enum PARAMETER_TYPE type;
  int* result;
  size_t i_row;
  size_t i_col;
  int set;
};

struct box_parameter {
  enum PARAMETER_TYPE type;
  int* result;
  size_t i_row;
  size_t i_col;
  size_t n_rows;
  size_t n_cols;
  int set;
};

struct list_parameter {
  enum PARAMETER_TYPE type;
  int* result;
  size_t i_row;
  size_t i_col;
  size_t length;
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
  for (enum PARAMETER_TYPE i = 0; i < PARAMETER_TYPE_LENGTH; ++i) {
    if (strcmp(parameter_type_string[i], type_str) == 0) return i;
  }
  
  return PARAMETER_NULL_TYPE;
}

struct method_parameter* new_parameter(enum PARAMETER_TYPE parameter_type) {
  struct method_parameter* result = NULL;

  size_t data_size = 0;
  switch (parameter_type) {
    case PARAMETER_POINT_TYPE:
      data_size = sizeof(struct point_parameter);
      break;
    case PARAMETER_BOX_TYPE:
      data_size = sizeof(struct box_parameter);
      break;
    case PARAMETER_LIST_TYPE:
      data_size = sizeof(struct list_parameter);
      break;
    default:
      return NULL;
  }

  result = calloc(data_size, 1);
  
  if (result == NULL) return NULL;
  
  result->type = parameter_type;
  result->result = NULL;

  return result;
}

enum TABLE_RESULT struct_parameter(struct method_parameter* parameter, char const* const parameter_string) {
  if (parameter == NULL) return TABLE_ERR_DATA_IS_NULL;
  char const* tok = NULL;

  switch (parameter->type) {
    case PARAMETER_POINT_TYPE: {
        struct point_parameter* point_parameter = 
          (struct point_parameter* )parameter;
        
        size_t length = 0;
        while ((tok = strtok(NULL, " ")) && length < 2) {
          switch (length) {
            case 0:
              point_parameter->i_row = atoi(tok);
              break;
            case 1:
              point_parameter->i_col = atoi(tok);
              break;
          }

          ++length;
        }

        if (length != 2) return TABLE_RESULT_FAIL;

        if (tok == NULL) return TABLE_RESULT_FAIL;
        point_parameter->set = atoi(tok);
      }
      break;
    case PARAMETER_BOX_TYPE: {
        struct box_parameter* box_parameter = 
          (struct box_parameter* )parameter;

        size_t length = 0;
        while ((tok = strtok(NULL, " ")) && length < 4) {
          switch (length) {
            case 0:
              box_parameter->i_row = atoi(tok);
              break;
            case 1:
              box_parameter->i_col = atoi(tok);
              break;
            case 2:
              box_parameter->n_rows = atoi(tok);
              break;
            case 3:
              box_parameter->n_cols = atoi(tok);
              break;
          }

          ++length;
        }

        if (length != 4) return TABLE_RESULT_FAIL;

        if (tok == NULL) return TABLE_RESULT_FAIL;
        box_parameter->set = atoi(tok);
      }
      break;
    case PARAMETER_LIST_TYPE: {
        struct list_parameter* list_parameter = 
          (struct list_parameter* )parameter;
        size_t length = 0;
        while ((tok = strtok(NULL, " ")) && length < 2) {
          switch (length) {
            case 0:
              list_parameter->i_row = atoi(tok);
              break;
            case 1:
              list_parameter->i_col = atoi(tok);
              break;
          }

          ++length;
        }

        if (length != 2) return TABLE_RESULT_FAIL;

        if ((tok = strtok(NULL, " ")) == NULL) return TABLE_RESULT_FAIL;
        list_parameter->length = atoi(tok);

        list_parameter->list = calloc(sizeof(int), list_parameter->length);
        for (int i = 0; i < list_parameter->length; ++i) {
          if ((tok = strtok(NULL, " ")) == NULL) break;
          list_parameter->list[i] = atoi(tok);
        }
      } 
      break;
    default:
      return TABLE_RESULT_FAIL;
  }

  return TABLE_RESULT_OK;
}

void clean_parameter(struct method_parameter* parameter) {
  if (parameter->type == PARAMETER_LIST_TYPE) {
    struct list_parameter* list_parameter = 
      (struct list_parameter* )parameter;
    if (list_parameter->list) free(list_parameter->list);
  }
}

#endif
