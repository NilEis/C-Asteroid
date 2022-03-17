#include "structs/list.h"
#include <stdio.h>
#include <stdlib.h>

struct list
{
    list_t *prev;
    list_t *next;
    void *value;
};

static void default_print_value(void *v);

list_t *list_new(void *value, list_t *prev)
{
    list_t *t = (list_t *)malloc(sizeof(list_t));
    t->prev = prev;
    t->next = NULL;
    t->value = value;
}

list_t *list_insert(list_t *l, void *value)
{
    list_t *ret = list_new(value, l);
    if (l == NULL)
    {
        return ret;
    }
    if (l->next != NULL)
    {
        l->next->prev = ret;
    }
    ret->next = l->next;
    l->next = ret;
    return l;
}

list_t *list_remove(list_t *l)
{
    list_t *ret = NULL;
    if (l == NULL)
    {
        return ret;
    }
    else if (l->prev != NULL)
    {
        if (l->next != NULL)
        {
            l->next->prev = l->prev;
            l->prev->next = l->next;
            ret = l->next;
        }
        else
        {
            l->prev->next = NULL;
            ret = l->prev;
        }
    }
    else
    {
        if (l->next != NULL)
        {
            l->next->prev = NULL;
            ret = l->next;
        }
        else
        {
            ret = NULL;
        }
    }
    free(l);
    l = NULL;
    return ret;
}

list_t *list_append(list_t *l, void *value)
{
    list_t *t = l;
    while (t->next != NULL)
    {
        t = t->next;
    }
    t->next = list_new(value, t->prev);
    return l;
}

list_t *list_get(void *value, list_t *l, int (*compare_values)(void *v1, void *v2))
{
    size_t i = list_length(l);
    list_t *t = l;
    while (i-- > 0)
    {
        if (compare_values(t->value, value) == 0)
        {
            return t;
        }
        else
        {
            t = t->next;
        }
    }
    return NULL;
}

void *list_get_value(list_t *l)
{
    if (l == NULL)
    {
        return NULL;
    }
    return l->value;
}

list_t *list_set_value(list_t *l, void *v)
{
    l->value = v;
    return l;
}

list_t *list_get_next(list_t *l)
{
    return l->next;
}

void list_printf(list_t *l, void (*print_value)(void *))
{
    list_t *t = l;
    if (print_value == NULL)
    {
        print_value = default_print_value;
    }
    printf("NULL: %p\n", NULL);
    printf("list {\n");
    size_t i = list_length(l);
    while (i-- > 0)
    {
        printf("-----------------------\nprev: %p\nnext: %p\nvalue: ", t->prev, t->next);
        print_value(t->value);
        t = t->next;
    }
    printf("}\n");
}

size_t list_length(list_t *l)
{
    if (l == NULL)
    {
        return 0;
    }
    size_t i = 1;
    while (l->next != NULL)
    {
        l = l->next;
        i++;
    }
    return i;
}

void list_clear(list_t *l)
{
    if (l == NULL)
    {
        return;
    }
    list_t *t = l;
    size_t i = list_length(l);
    while (t->next != NULL)
    {
        l = t->next;
        free(t);
        t = NULL;
        t = l;
    }
}

void list_foreach(list_t *l, void (*f)(void *))
{
    list_t *t = l;
    size_t i = list_length(l);
    while (i-- > 0)
    {
        f(t->value);
        t = t->next;
    }
}

static void default_print_value(void *v)
{
    printf("%p\n", v);
}