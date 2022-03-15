#include "video/video_main.h"
#include "raylib.h"

int video_init(int width, int height, const char *title)
{
    InitWindow(width, height, title);
    SetTargetFPS(60);
    return 0;
}