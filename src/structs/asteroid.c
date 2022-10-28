#include "structs/asteroid.h"
#include "game/functions.h"
#include <stdlib.h>
#include <math.h>

#define conv(x, s) (((double)(x) / 1000.0) * ((double)s))

static uint16_t c_id = 0;

static int draw_hitbox = 0;

static uint16_t num_asteroids = 0;

uint16_t asteroid_get_num(void)
{
    return num_asteroids;
}

asteroid_t *asteroid_new(uint16_t x, uint16_t y, uint8_t size)
{
    asteroid_t *t = (asteroid_t *)malloc(sizeof(asteroid_t));
    if (t == NULL)
    {
        return NULL;
    }
    t->x = x % 1000;
    t->y = y % 1000;
    int va = rand() % 360;
    t->vx = 40 * cos(va);
    t->vy = 40 * sin(va);
    t->id = c_id++;
    float a = rand() % 360;
    double r = 0;
    double max_r = 1;
    for (int i = 0; i < 15; i++)
    {
        r = (double)((rand() % (size / 2)) + size);
        if (r > max_r)
        {
            max_r = r;
        }
        t->verticies[i].x = cosf(DEG2RAD * (360 - a)) * r;
        t->verticies[i].y = sinf(DEG2RAD * (360 - a)) * r;
        a += 24;
    }
    t->r = max_r;
    t->dead = 0;
    num_asteroids++;
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
    if (draw_hitbox)
    {
        DrawCircleLines(conv(t->x, width), conv(t->y, height), conv(t->r, width), RED);
    }
}

int asteroid_hit(asteroid_t *a, int x, int y, int r)
{
    int distX = a->x - x;
    int distY = a->y - y;
    int distR = a->r + r;
    return (distX * distX + distY * distY) <= (distR * distR);
}

void asteroid_update(asteroid_t *t, double time)
{
    if (t == NULL)
    {
        return;
    }
    t->x = lerp_precise(t->x, t->x + t->vx, time);
    t->y = lerp_precise(t->y, t->y + t->vy, time);
    t->x = (t->x < 0) * (1000) + (t->x >= 0) * (t->x % 1000);
    t->y = (t->y < 0) * (1000) + (t->y >= 0) * (t->y % 1000);
}

void asteroid_break(asteroid_t *a, asteroid_t **arr, int index, int size)
{
    double r = a->r;
    uint16_t x = a->x;
    uint16_t y = a->y;
    asteroid_free(a);

    if (r / 2.0 <= 16.0)
    {
        arr[index] = NULL;
    }
    else
    {
        arr[index] = asteroid_new(x, y, r / 2);
        asteroid_add(asteroid_new(x, y, r / 2), arr, size);
    }
}

int asteroid_add(asteroid_t *a, asteroid_t **arr, int size)
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
    asteroid_free(a);
    return 1;
}

void asteroid_tick(void *t, int width, int height, asteroid_t **arr, int index, double time)
{
    asteroid_t *a = (asteroid_t *)t;
    asteroid_draw(a, width, height);
    a = arr[index];
    asteroid_update(a, time);
}

inline void asteroid_free(asteroid_t *t)
{
    num_asteroids--;
    free(t);
}

void asteroid_switch_hitbox(void)
{
    draw_hitbox = !draw_hitbox;
}