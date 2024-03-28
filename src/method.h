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

extern char const* parameter_type_string[PARAMETER_TYPE_LENGTH];

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

#define TABLE_FUNCTION_H(X) enum TABLE_RESULT X (struct table* table, struct method_parameter* parameter);

#define TABLE_FUNCTION(X, Y) enum TABLE_RESULT X (struct table* table, struct method_parameter* parameter) { \
  if (table == NULL) return TABLE_ERR_TABLE_IS_NULL; \
  if (table->data == NULL) return TABLE_ERR_DATA_IS_NULL; \
  Y; return TABLE_ERR_NOT_IMPLEMENTED; }

TABLE_FUNCTION_H(set);
TABLE_FUNCTION_H(get);
TABLE_FUNCTION_H(sum);
TABLE_FUNCTION_H(average);
TABLE_FUNCTION_H(max);
TABLE_FUNCTION_H(min);
TABLE_FUNCTION_H(append);
TABLE_FUNCTION_H(delete);
TABLE_FUNCTION_H(not_implemented);

enum PARAMETER_TYPE get_parameter_type(char const* const type_str);
struct method_parameter* new_parameter(enum PARAMETER_TYPE parameter_type);
enum TABLE_RESULT struct_parameter(struct method_parameter* parameter, char const* const parameter_string);
void clean_parameter(struct method_parameter* parameter);

#endif
