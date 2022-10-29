/**
 * @file player.h
 * @author NilEis
 * @brief the module for the player
 * @date 2022-10-29
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef PLAYER_H
#define PLAYER_H

/**
 * @brief Initialises the player
 * 
 */
void player_init();

/**
 * @brief Draws the player
 * 
 * @param width The width  of the window
 * @param height The height  of the window
 */
void player_draw(int width, int height);

/**
 * @brief Updates the player
 * 
 * @param time frametime
 * @return int 1 if spacebar is pressed
 */
int player_update(double time);

/**
 * @brief Draws and updates the player
 * 
 * @param width the width of the window
 * @param height the height of the window
 * @param time frametime
 * @return int 1 if the spacebar is pressed
 */
int player_tick(int width, int height, double time);

/**
 * @brief returns the x position
 * 
 * @return int x position
 */
int player_get_x();

/**
 * @brief returns the y position
 * 
 * @return int y position
 */
int player_get_y();

/**
 * @brief Returns the velocity
 * 
 * @return double velocity
 */
double player_get_v(void);

/**
 * @brief Returns the angle
 * 
 * @return float angle
 */
float player_get_a();

/**
 * @brief Returns the size of the player
 * 
 * @return int size
 */
int player_get_size();

/**
 * @brief Turns the hitbox on/off
 * 
 */
void player_switch_hitbox(void);

#endif // PLAYER_H
