#include "structs/bullet.h"
#include "game/functions.h"
#include <math.h>
#include <stdlib.h>
#include "raylib.h"

#define conv(x, s) (((double)(x) / 1000.0) * ((double)s))

#define V 65

#define R 1.25

static int draw_hitbox = 0;

static double time = 0;

bullet_t *bullet_new(int16_t x, int16_t y, float a, double v)
{
    double tmp = GetTime();
    if (tmp - time >= 0.1)
    {
        bullet_t *b = (bullet_t *)malloc(sizeof(bullet_t));
        b->x = x;
        b->y = y;
        b->vx = (v + V) * cos(a);
        b->vy = (v + V) * sin(a);
        b->i = 0;
        time = GetTime();
        return b;
    }
    return NULL;
}

void bullet_update(bullet_t *b, double time)
{
    b->x = lerp_precise(b->x, b->x + b->vx, time);
    b->x = (b->x < 0) * (1000) + (b->x >= 0) * (b->x % 1000);
    b->y = lerp_precise(b->y, b->y + b->vy, time);
    b->y = (b->y < 0) * (1000) + (b->y >= 0) * (b->y % 1000);
    b->i += 1;
}

void bullet_draw(bullet_t *b, int width, int height)
{
    DrawCircle(conv(b->x, width), conv(b->y, height), R, WHITE);
    if (draw_hitbox)
    {
        DrawCircleLines(conv(b->x, width), conv(b->y, height), R, RED);
    }
}

int bullet_tick(bullet_t *b, int width, int height, double time)
{
    bullet_draw(b, width, height);
    bullet_update(b, time);
    return b->i >= 50;
}

int bullet_collide(asteroid_t *a, bullet_t *b)
{
    double distX = a->x - b->x;
    double distY = a->y - b->y;
    double distR = a->r + R;
    return (distX * distX + distY * distY) <= (distR * distR);
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

inline void bullet_free(bullet_t *b)
{
    free(b);
}

void bullet_switch_hitbox(void)
{
    draw_hitbox = !draw_hitbox;
}