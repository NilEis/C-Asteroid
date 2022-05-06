#ifndef ASTEROID_H
#define ASTEROID_H

#include <stdint.h>
#include "raylib.h"

typedef struct asteroid asteroid_t;

struct asteroid
{
    int16_t x;
    int16_t y;
    int8_t vx;
    int8_t vy;
    uint16_t id;
    Vector2 verticies[15];
    float r;
};

asteroid_t *asteroid_new(uint16_t x, uint16_t y, uint8_t size);

int asteroid_compare(void *a1, void *a2);

void asteroid_draw(asteroid_t *t, int width, int height);

int asteroid_hit(asteroid_t *a, int x, int y, int r);

void asteroid_update(asteroid_t *t, double time);

void asteroid_break(asteroid_t *a, asteroid_t **arr, int index, int size);

int asteroid_add(asteroid_t *a, asteroid_t **arr, int size);

void asteroid_tick(void *t, int width, int height, asteroid_t **arr, int index, double time);

void asteroid_free(asteroid_t *t);

void asteroid_switch_hitbox(void);

#endif // ASTEROID_H
