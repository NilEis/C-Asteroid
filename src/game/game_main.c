#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "game/game_main.h"
#include "video/video_main.h"
#include "structs/asteroid.h"
#include "structs/bullet.h"
#include "structs/player.h"
#include "structs/particle.h"
#include <stdio.h>

static int monitor = 0;
static int width = 0;
static int height = 0;
static uint8_t invincible = 0;
static asteroid_t *asteroids[512] = {NULL};
static const int asteroids_size = sizeof(asteroids) / sizeof(asteroid_t *);
static bullet_t *bullets[64] = {NULL};
static const int bullets_size = sizeof(bullets) / sizeof(bullet_t *);

static void (*game_active)(void) = NULL;

static double last_time = 0;

static void cleanup(void);
static void game_start(void);
static void game_run(void);
static void game_end(void);

void game_init()
{
    time_t t;
    srand((unsigned)time(&t));
    int x = rand();
    int y = rand();
    player_init();
    particle_init();
    atexit(cleanup);
    for (int i = 0; i < asteroids_size; i++)
    {
        asteroids[i] = NULL;
    }
    for (int i = 0; i < 15; i++)
    {
        if (rand() % 2)
        {
            x = rand();
            y = (rand() % 2 == 0) * 1000;
        }
        else
        {
            x = (rand() % 2 == 0) * 1000;
            y = rand();
        }
        asteroids[i] = asteroid_new(x, y, 25);
    }
    game_active = game_start;
    last_time = GetTime();
}

void game_tick()
{
    monitor = GetCurrentMonitor();
    if (IsKeyPressed(KEY_F))
    {
        SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
        SetWindowState(FLAG_WINDOW_UNDECORATED);
        SetWindowPosition(0, 0);
    }
    game_active();
}

static void game_start(void)
{
    if (IsKeyPressed(KEY_SPACE))
    {
        game_active = game_run;
    }
    DrawText("PRESS SPACE TO START", 25, height / 2, height / 25, WHITE);
}

static void game_run(void)
{
    double frame_time = 1.0 - pow(0.001, GetTime() - last_time);
    monitor = GetCurrentMonitor();
    if (IsKeyPressed(KEY_H))
    {
        asteroid_switch_hitbox();
        bullet_switch_hitbox();
        player_switch_hitbox();
    }
    if (IsKeyPressed(KEY_I))
    {
        invincible = !invincible;
    }
    if (player_tick(width, height, frame_time) == 1)
    {
        bullet_add(bullet_new(player_get_x(), player_get_y(), player_get_a(), player_get_v()), bullets, bullets_size);
    }
    for (int i = 0; i < bullets_size; i++)
    {
        if (bullets[i] != NULL)
        {
            if (bullet_tick(bullets[i], width, height, frame_time))
            {
                bullet_free(bullets[i]);
                bullets[i] = NULL;
            }
        }
    }
    for (int i = 0; i < asteroids_size; i++)
    {
        int colllide = 0;
        if (asteroids[i] != NULL)
        {
            asteroid_tick(asteroids[i], width, height, asteroids, i, frame_time);
            if (!invincible && asteroid_hit(asteroids[i], player_get_x(), player_get_y(), player_get_size()))
            {
                game_active = game_end;
            }
            for (int j = 0; j < bullets_size && colllide == 0; j++)
            {
                if (bullets[j] != NULL)
                {
                    if (bullet_collide(asteroids[i], bullets[j]))
                    {
                        int num_p = rand() % 128;
                        for (int k = 0; k < num_p; k++)
                        {
                            particle_add(bullets[j]->x, bullets[j]->y, rand() % 360, 25 + rand() % 20);
                        }
                        colllide = 1;
                        bullet_free(bullets[j]);
                        bullets[j] = NULL;
                        asteroid_break(asteroids[i], asteroids, i, asteroids_size);
                        break;
                    }
                }
            }
        }
    }
    particle_tick(width, height, frame_time);
    last_time = GetTime();
}

void game_set_width(int w)
{
    width = w;
}

void game_set_height(int h)
{
    height = h;
}

static void game_end(void)
{
    game_init();
    DrawText("PRESS ESC TO EXIT", height / 25, height / 2, height / 25, WHITE);
}

static void cleanup(void)
{
    for (int i = 0; i < asteroids_size; i++)
    {
        asteroid_free(asteroids[i]);
    }
}