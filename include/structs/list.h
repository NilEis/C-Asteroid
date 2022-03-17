#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

typedef struct list list_t;

list_t *list_new(void *value, list_t *prev);

list_t *list_insert(list_t *l, void *value);

list_t *list_remove(list_t *l);

list_t *list_append(list_t *l, void *value);

list_t *list_get(void *value, list_t *l, int (*compare_values)(void *v1, void *v2));

void *list_get_value(list_t *l);

list_t *list_set_value(list_t *l, void *v);

list_t *list_get_next(list_t *l);

void list_printf(list_t *l, void (*print_value)(void *));

size_t list_length(list_t *l);

void list_clear(list_t *l);

void list_foreach(list_t *l, void (*f)(void *));

#endif // LIST_H
