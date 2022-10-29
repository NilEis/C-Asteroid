/**
 * @file bullet.h
 * @author NilEis
 * @brief The module for the bullets
 * @date 2022-10-29
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef BULLET_H
#define BULLET_H

#include <stdint.h>

#include "structs/asteroid.h"

typedef struct bullet bullet_t; ///< typedef

/**
 * @brief The struct for the bullets
 */
struct bullet
{
    int16_t x; ///< x position
    int16_t y; ///< y position
    int16_t vx; ///< x velocity
    int16_t vy; ///< y velocity
    int16_t i; ///< the lifetime of the bullet
};

/**
 * @brief Creates a new bullet
 * 
 * @param x x position
 * @param y y position
 * @param a angle
 * @param v speed
 * @return bullet_t* the bullet or NULL
 */
bullet_t *bullet_new(int16_t x, int16_t y, float a, double v);

/**
 * @brief Updates a bullet
 * 
 * @param b the bullet
 * @param time the frametime
 */
void bullet_update(bullet_t *b, double time);

/**
 * @brief Draws a bullet
 * 
 * @param b the bullet
 * @param width the width of the window
 * @param height the height of the window
 */
void bullet_draw(bullet_t *b, int width, int height);

/**
 * @brief Draws and updates a bullet
 * 
 * @param b the bullet
 * @param width the width of the window
 * @param height the height of the window
 * @param time frametime
 * @return int the lifetime of the bullet
 */
int bullet_tick(bullet_t *b, int width, int height, double time);

/**
 * @brief Tests if an asteroid collides with a bullet
 * 
 * @param a the asteroid
 * @param b the bullet
 * @return int 1 if true 0 if false
 */
int bullet_collide(asteroid_t *a, bullet_t *b);

/**
 * @brief Adds a bullet to the array
 * 
 * @param a the bullet
 * @param arr the array
 * @param size the size of the array
 * @return int 0 if successful 1 if not
 */
int bullet_add(bullet_t *a, bullet_t **arr, int size);

/**
 * @brief Frees the memory of a bullet
 * 
 * @param t the bullet
 */
void bullet_free(bullet_t *t);

/**
 * @brief Turns the hitbox on/off
 * 
 */
void bullet_switch_hitbox(void);

#endif // BULLET_H
