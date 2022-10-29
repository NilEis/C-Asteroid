/**
 * @file asteroid.h
 * @author NilEis
 * @brief the module for the asteroid
 * @date 2022-10-29
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef ASTEROID_H
#define ASTEROID_H

#include <stdint.h>
#include "raylib.h"

typedef struct asteroid asteroid_t; ///< typedef

/**
 * @brief The asteroid struct defines the asteroids in the game
 */
struct asteroid
{
    int16_t x; ///< x position
    int16_t y; ///< y Position
    int8_t vx; ///< speed in the x direction
    int8_t vy; ///< speed in the y direction
    uint16_t id; ///< the id of the asteroid
    Vector2 verticies[15]; ///< the verticies
    float r; ///< radius/size
};

/**
 * @brief Returns the amount of asteroids
 * 
 * @return uint16_t number of asteroids
 */
uint16_t asteroid_get_num(void);

/**
 * @brief Generates a new asteroid
 * 
 * @param x x position
 * @param y y position
 * @param size size of the algorithm
 * @return asteroid_t* the new asteroid or NULL
 */
asteroid_t *asteroid_new(uint16_t x, uint16_t y, uint8_t size);

/**
 * @brief Draws an asteroid
 * 
 * @param t the asteroid
 * @param width the width of the window
 * @param height the height of the window
 */
void asteroid_draw(asteroid_t *t, int width, int height);

/**
 * @brief Tests if a point is inside the asteroid
 * 
 * @param a the asteroid
 * @param x x position
 * @param y y position
 * @param r radius of the hitbos
 * @return int 0 if false 1 if true
 */
int asteroid_hit(asteroid_t *a, int x, int y, int r);

/**
 * @brief updates an asteroid
 * 
 * @param t the asteroid
 * @param time frametime
 */
void asteroid_update(asteroid_t *t, double time);

/**
 * @brief Breaks an asteroid or destroys it
 * 
 * @param a the asteroid
 * @param arr the array of the asteroid
 * @param index the index of the asteroid
 * @param size the size the array
 */
void asteroid_break(asteroid_t *a, asteroid_t **arr, int index, int size);

/**
 * @brief Adds an asteroid
 * 
 * @param a the asteroid
 * @param arr the array
 * @param size the size of the array
 * @return int 0 if the asteroid is added 1 if no place was found and the asteroid was freed
 */
int asteroid_add(asteroid_t *a, asteroid_t **arr, int size);

/**
 * @brief Updates and draws an asteroid
 * 
 * @param t the asteroid
 * @param width the game width
 * @param height the game height
 * @param arr the array of the asteroid
 * @param index the index of the asteroid
 * @param time frametime
 */
void asteroid_tick(void *t, int width, int height, asteroid_t **arr, int index, double time);

/**
 * @brief frees the memory of the asteroid
 * 
 * @param t the asteroid
 */
void asteroid_free(asteroid_t *t);

/**
 * @brief turns the hitbox on/off
 * 
 */
void asteroid_switch_hitbox(void);

#endif // ASTEROID_H
