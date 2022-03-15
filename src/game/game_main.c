#include "game/game_main.h"

#include <math.h>
#include <time.h>
#include "structs/list.h"
#include "structs/asteroid.h"
#include "structs/player.h"

static int monitor = 0;
static int width = 0;
static int height = 0;
static list_t *l = NULL;

static void cleanup(void);

void game_init()
{
    time_t t;
    srand((unsigned)time(&t));
    int x = rand();
    int y = rand();
    l = list_new(asteroid_new(x, y, 21), NULL);
    player_init();
    atexit(cleanup);
    for (int i = 0; i < 0; i++)
    {
        x = rand();
        y = rand();
        list_append(l, asteroid_new(x, y, 21));
    }
}

void game_tick()
{
    monitor = GetCurrentMonitor();
    width = GetScreenWidth();
    height = GetScreenHeight();

    int i = list_length(l);
    player_tick(width, height);
    list_t *x = l;
    while (i-- && x != NULL)
    {
        printf("%p\n", x);
        asteroid_tick((asteroid_t *)list_get_value(x), width, height, l);
        x = list_get_next(x);
    }
    printf("%p\n---------------\n", l);
}

static void cleanup(void)
{
    list_foreach(l, asteroid_free);
    list_clear(l);
}