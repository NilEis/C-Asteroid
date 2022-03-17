#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "game/game_main.h"
#include "structs/asteroid.h"
#include "structs/bullet.h"
#include "structs/player.h"

static int monitor = 0;
static int width = 0;
static int height = 0;
static asteroid_t *asteroids[100] = {NULL};
static const int asteroids_size = sizeof(asteroids) / sizeof(asteroid_t *);
static bullet_t *bullets[100] = {NULL};
static const int bullets_size = sizeof(bullets) / sizeof(bullet_t *);

static void cleanup(void);

void game_init()
{
    time_t t;
    srand((unsigned)time(&t));
    int x = rand();
    int y = rand();
    player_init();
    atexit(cleanup);
    for (int i = 0; i < asteroids_size; i++)
    {
        asteroids[i] = NULL;
    }
    for (int i = 0; i < 3; i++)
    {
        x = rand();
        y = rand();
        asteroids[i] = asteroid_new(x, y, 25);
    }
}

void game_tick()
{
    monitor = GetCurrentMonitor();
    width = GetScreenWidth();
    height = GetScreenHeight();
    if (player_tick(width, height) == 1)
    {
        bullet_add(bullet_new(player_get_x(), player_get_y(), player_get_a()), bullets, bullets_size);
    }
    for (int i = 0; i < bullets_size; i++)
    {
        if (bullets[i] != NULL)
        {
            bullet_tick(bullets[i], width, height, bullets, i, bullets_size);
        }
    }
    for (int i = 0; i < asteroids_size; i++)
    {
        if (asteroids[i] != NULL)
        {
            asteroid_tick(asteroids[i], width, height, asteroids, i, asteroids_size);
        }
    }
}

static void cleanup(void)
{
    for (int i = 0; i < asteroids_size; i++)
    {
        asteroid_free(asteroids[i]);
    }
}