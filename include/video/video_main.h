/**
 * @file video_main.h
 * @author NilEis
 * @brief the video module
 * @date 2022-10-29
 * 
 * @copyright Copyright (c) 2022
 */
#ifndef VIDEO_MAIN_H
#define VIDEO_MAIN_H

#include "raylib.h"

/**
 * @brief Initialises the video module
 * 
 * @param width the width of the window
 * @param height the height of the window
 * @param title the title of the window
 * @return int 0
 */
int video_init(int width, int height, const char *title);

#endif // VIDEO_MAIN_H
