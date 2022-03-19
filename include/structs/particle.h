#ifndef PARTICLE_H
#define PARTICLE_H

typedef struct particle particle_t;

struct particle
{
    double x;
    double y;
    double vx;
    double vy;
    double i;
};

void particle_init();

int particle_add(int x, int y, double a, int i);

void particle_tick(int width, int height);

int particle_update(particle_t *p);

void particle_draw(particle_t *p, int width, int height);

void particle_free(particle_t *p);

#endif // PARTICLE_H
