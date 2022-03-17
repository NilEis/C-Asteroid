#ifndef BULLET_H
#define BULLET_H

#include <stdint.h>

typedef struct bullet bullet_t;

struct bullet
{
    int16_t x;
    int16_t y;
    int16_t vx;
    int16_t vy;
    int16_t i;
};

bullet_t *bullet_new(int16_t x, int16_t y, float a);

void bullet_update(bullet_t *b);

void bullet_draw(bullet_t *b, int width, int height);

void bullet_tick(bullet_t *b, int width, int height, bullet_t **arr, int index, int size);

int bullet_add(bullet_t *a, bullet_t **arr, int size);

#endif // BULLET_H
