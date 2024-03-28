#ifndef __LIST_H
#define __LIST_H

#include "common.h"

struct list {
  struct list* next;
  struct list* prev;
  int data;
};

void list_append(struct list* list, int input);
void list_make(struct list** list, size_t length);
void list_clean(struct list** list);
struct list* list_get_node(struct list* list, size_t index);
int list_get(struct list* list, size_t index);
void list_set(struct list* list, size_t index, int input);

#endif
