#include "structs/particle.h"
#include "game/functions.h"
#include <stdlib.h>
#include <math.h>
#include "raylib.h"

#define conv(x, s) (((double)(x) / 1000.0) * ((double)s))

static particle_t *particles[8192];
static const int particles_size = sizeof(particles) / sizeof(particle_t *);

static int num_particles = 0;

void particle_init()
{
    for (int i = 0; i < particles_size; i++)
    {
        particles[i] = NULL;
    }
}

int particle_add(int x, int y, double a, int i)
{
    particle_t *p = (particle_t *)malloc(sizeof(particle_t));
    p->x = x;
    p->y = y;
    p->vx = cos(a) * 70.0;
    p->vy = sin(a) * 70.0;
    p->i = i;
    int j = 0;
    while (particles[j] != NULL && j < particles_size)
    {
        j++;
    }
    particles[j] = p;
    num_particles++;
    return 0;
}

void particle_tick(int width, int height, double time)
{
    for (int i = 0; i < particles_size && num_particles > 0; i++)
    {
        if (particles[i] != NULL)
        {
            if (particle_update(particles[i], time) == 1)
            {
                particle_free(particles[i]);
                particles[i] = NULL;
            }
            else
            {
                particle_draw(particles[i], width, height);
            }
        }
    }
}

int particle_update(particle_t *p, double time)
{
    p->x = lerp_precise(p->x, p->x + p->vx, time);
    p->y = lerp_precise(p->y, p->y + p->vy, time);
    p->i--;
    if (p->i <= 0 || p->x < 0 || p->x >= 1000 || p->y < 0 || p->y >= 1000)
    {
        return 1;
    }
    return 0;
}

void particle_draw(particle_t *p, int width, int height)
{
    DrawPixel(conv(p->x, width), conv(p->y, height), RAYWHITE);
    // DrawCircle(conv(p->x, width), conv(p->y, height), 2, RAYWHITE);
}

inline void particle_free(particle_t *p)
{
    free(p);
    num_particles--;
}