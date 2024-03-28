#include "list.h"

void list_append(struct list* list, int input) {
  while (list->next != NULL) {
    list = list->next;
  }

  list->next = (struct list* )malloc(sizeof(struct list));
  *list->next = (struct list) {
    .next = NULL,
    .prev = list,
    .data = input,
  };
}

void list_make(struct list** list, size_t length) {
  if (list == NULL) return;
  if (*list == NULL) {
    *list = (struct list* )malloc(sizeof(struct list));
    **list = (struct list) {
      .next = NULL,
      .prev = NULL,
      .data = 0,
    };
  }
  
  for (size_t i = 1; i < length; ++i) {
    list_append(*list, 0);
    list = &(*list)->next;
  }
}

void list_clean(struct list** list) {
  struct list* freed = NULL;
  while (list) {
    if (freed) free(freed);
    freed = *list;
    list = &(*list)->next;
  }

  if (freed) free(freed);
}

struct list* list_get_node(struct list* list, size_t index) {
  for (int i = 0; i < index && list; ++i) list = list->next;

  return list;
}

int list_get(struct list* list, size_t index) {
  for (int i = 0; i < index && list; ++i) list = list->next;

  return list->data;
}

void list_set(struct list* list, size_t index, int input) {
  list = list_get_node(list, index);
  if (list == NULL)
    return;

  list->data = input;
}
