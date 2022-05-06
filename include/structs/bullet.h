#ifndef BULLET_H
#define BULLET_H

#include <stdint.h>

#include "structs/asteroid.h"

typedef struct bullet bullet_t;

struct bullet
{
    int16_t x;
    int16_t y;
    int16_t vx;
    int16_t vy;
    int16_t i;
};

bullet_t *bullet_new(int16_t x, int16_t y, float a, double v);

void bullet_update(bullet_t *b, double time);

void bullet_draw(bullet_t *b, int width, int height);

int bullet_tick(bullet_t *b, int width, int height, double time);

int bullet_collide(asteroid_t *a, bullet_t *b);

int bullet_add(bullet_t *a, bullet_t **arr, int size);

void bullet_free(bullet_t *t);

void bullet_switch_hitbox(void);

#endif // BULLET_H
