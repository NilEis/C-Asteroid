/**
 * @file game_main.h
 * @author NilEis
 * @brief the game module
 * @date 2022-10-29
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef GAME_MAIN_H
#define GAME_MAIN_H

/**
 * @brief Initialise the game module
 */
void game_init();

/**
 * @brief Run one tick 
 */
void game_tick();

/**
 * @brief Set the width of the game
 * 
 * @param w The new width
 */
void game_set_width(int w);

/**
 * @brief Set the height of the game
 * 
 * @param h The new height
 */
void game_set_height(int h);

#endif // GAME_MAIN_H
