/**
 * @file particle.h
 * @author NilEis
 * @brief The module for particles
 * @date 2022-10-29
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef PARTICLE_H
#define PARTICLE_H
#include "raylib.h"

typedef struct particle particle_t; ///< typedef

/**
 * @brief Defines the particle
 * 
 */
struct particle
{
    double x; ///< x position
    double y; ///< y position
    double vx; ///< x velocity
    double vy; ///< y velocity
    double i; ///< lifetime
    Color c; ///< color
};

/**
 * @brief Initialises the particle module
 * 
 */
void particle_init();

/**
 * @brief Adds a new particle
 * 
 * @param x x position
 * @param y y position
 * @param a angle
 * @param i lifetime
 * @return int -1 if the particle could not created, otherwise 0
 */
int particle_add(int x, int y, double a, int i);

/**
 * @brief Updates and draws the particle
 * 
 * @param width the width of the window
 * @param height the height of the window
 * @param time frametime
 */
void particle_tick(int width, int height, double time);

/**
 * @brief Updates a particle
 * 
 * @param p the particle
 * @param time frametime
 * @return int 1 if the particle died otherwise 0
 */
int particle_update(particle_t *p, double time);

/**
 * @brief Draws a particle
 * 
 * @param p the particle
 * @param width the width  of the window
 * @param height the height  of the window
 */
void particle_draw(particle_t *p, int width, int height);

/**
 * @brief Frees the memory of a particle
 * 
 * @param p the particle
 */
void particle_free(particle_t *p);

#endif // PARTICLE_H
