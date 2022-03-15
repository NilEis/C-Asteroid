#ifndef ASTEROID_H
#define ASTEROID_H

#include <stdint.h>
#include "raylib.h"
#include "structs/list.h"

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

void asteroid_update(asteroid_t *t);

void asteroid_tick(void *t, int width, int height, list_t *l);

void asteroid_free(void *t);

#endif // ASTEROID_H
