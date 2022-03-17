#include "structs/bullet.h"
#include <math.h>
#include <stdlib.h>
#include "raylib.h"

#define conv(x, s) (((double)(x) / 1000.0) * ((double)s))

#define V 5

bullet_t *bullet_new(int16_t x, int16_t y, float a)
{
    bullet_t *b = (bullet_t *)malloc(sizeof(bullet_t));
    b->x = x;
    b->y = y;
    b->vx = V * cos(a);
    b->vy = V * sin(a);
    b->i = 0;
}

void bullet_update(bullet_t *b)
{
    b->x += b->vx;
    b->x = (b->x < 0) * (1000) + (b->x>=0)*(b->x % 1000);
    b->y += b->vy;
    b->y = (b->y < 0) * (1000) + (b->y>=0)*(b->y % 1000);
    b->i += 1;
}

void bullet_draw(bullet_t *b, int width, int height)
{
    DrawCircleLines(conv(b->x, width), conv(b->y, height), 5, WHITE);
}

void bullet_tick(bullet_t *b, int width, int height, bullet_t **arr, int index, int size)
{
    bullet_draw(b, width, height);
    bullet_update(b);
}

int bullet_add(bullet_t *a, bullet_t **arr, int size)
{
    int i = 0;
    while (arr[i] != NULL && i < size)
    {
        i++;
    }
    if (i < size)
    {
        arr[i] = a;
        return 0;
    }
    return 1;
}