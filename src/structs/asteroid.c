#include "structs/asteroid.h"
#include <stdlib.h>
#include <math.h>

static uint16_t c_id = 0;

asteroid_t *asteroid_new(uint16_t x, uint16_t y, uint8_t size)
{
    asteroid_t *t = (asteroid_t *)malloc(sizeof(asteroid_t));
    if (t == NULL)
    {
        return NULL;
    }
    t->x = x % 1000;
    t->y = y % 1000;
    t->vx = 1 + ((rand() % 100) - 50) / 10;
    t->vy = 1 + ((rand() % 100) - 50) / 10;
    t->id = c_id++;
    float a = rand() % 360;
    double r = 0;
    double max_r = -1;
    for (int i = 0; i < 15; i++)
    {
        r = (double)((rand() % (size / 2)) + size);
        max_r = (max_r <= r) * max_r + (r > max_r) * r;
        t->verticies[i].x = cosf(DEG2RAD * (360 - a)) * r;
        t->verticies[i].y = sinf(DEG2RAD * (360 - a)) * r;
        a += 24;
    }
    t->r = max_r;
    return t;
}

int asteroid_compare(void *a1, void *a2)
{
    return (((asteroid_t *)a1)->id < ((asteroid_t *)a2)->id) * (-1) + (((asteroid_t *)a1)->id > ((asteroid_t *)a2)->id) * 1;
}

void asteroid_draw(asteroid_t *t, int width, int height)
{
    if (t == NULL)
    {
        return;
    }
    for (int i = 1; i < 15; i++)
    {
        DrawLine(((float)(t->x + t->verticies[i - 1].x) / 1000.0) * width, ((float)(t->y + t->verticies[i - 1].y) / 1000.0) * height, ((float)(t->x + t->verticies[i].x) / 1000.0) * width, ((float)(t->y + t->verticies[i].y) / 1000.0) * height, WHITE);
    }
    DrawLine(((float)(t->x + t->verticies[14].x) / 1000.0) * width, ((float)(t->y + t->verticies[14].y) / 1000.0) * height, ((float)(t->x + t->verticies[0].x) / 1000.0) * width, ((float)(t->y + t->verticies[0].y) / 1000.0) * height, WHITE);
}

void asteroid_update(asteroid_t *t)
{
    if (t == NULL)
    {
        return;
    }
    t->x += t->vx;
    t->y += t->vy;
    t->x = (t->x < 0) * (1000) + (t->x >= 0) * (t->x % 1000);
    t->y = (t->y < 0) * (1000) + (t->y >= 0) * (t->y % 1000);
}

list_t *asteroid_break(asteroid_t *a, list_t *l)
{
    list_t *la = list_get((void *)a, l, asteroid_compare);
    list_t *ret = NULL;
    if (la == NULL)
    {
        return;
    }
    double r = a->r;
    uint16_t x = a->x;
    uint16_t y = a->y;
    asteroid_free(a);
    list_set_value(la, NULL);
    if (r <= 3.0)
    {
        ret = list_remove(la);
    }
    else
    {
        ret = list_set_value(la, asteroid_new(x, y, r / 2));
        list_insert(la, asteroid_new(x, y, r / 2));
    }
    return ret;
}

list_t *asteroid_tick(void *t, int width, int height, list_t *l)
{
    list_t *ret = l;
    ret = asteroid_break((asteroid_t *)t, l);
    asteroid_draw((asteroid_t *)t, width, height);
    asteroid_update((asteroid_t *)t);
    return ret;
}

inline void asteroid_free(void *t)
{
    free(t);
    t = NULL;
}