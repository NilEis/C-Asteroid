#include "structs/player.h"
#include "game/functions.h"
#include <math.h>
#include <float.h>
#include "raylib.h"
#include "rlgl.h"

#define conv(x, s) (((double)(x) / 1000.0) * ((double)s))

#define PLAYER_SIZE 4.0
#define MAX_V2 (MAX_V * MAX_V)
#define MAX_V 65.0

static int draw_hitbox = 0;

int x = 0;
int y = 0;
double va = 1.1;
double vx = 0;
double vy = 0;

void player_init()
{
    x = 500;
    y = 500;
    va = 1.0;
    vx = 0;
    vy = 0;
}

void player_draw(int width, int height)
{
    double vd_x = cos(va) * 1.2;
    double vd_y = sin(va) * 1.2;
    double n_x = 1;
    double sin_va = sin(va);
    double n_y = -(cos(va) / (sin_va == 0 ? DBL_MIN : sin_va));
    const double v_l = sqrt(1 + n_y * n_y);
    static const double p_length = 5.0 * PLAYER_SIZE;
    static const double p_width = 2.25 * PLAYER_SIZE;
    static const double p_tail = 2.5 * PLAYER_SIZE;
    n_x /= v_l;
    n_y /= v_l;
    DrawLine(conv(x + vd_x * p_length, width), conv(y + vd_y * p_length, height), conv(-vd_x * p_tail + x + n_x * p_width, width), conv(-vd_y * p_tail + y + n_y * p_width, height), WHITE);
    DrawLine(conv(-vd_x * p_tail + x + n_x * p_width, width), conv(-vd_y * p_tail + y + n_y * p_width, height), conv(x, width), conv(y, height), WHITE);
    DrawLine(conv(x, width), conv(y, height), conv(-vd_x * p_tail + x - n_x * p_width, width), conv(-vd_y * p_tail + y - n_y * p_width, height), WHITE);
    DrawLine(conv(-vd_x * p_tail + x - n_x * p_width, width), conv(-vd_y * p_tail + y - n_y * p_width, height), conv(x + vd_x * p_length, width), conv(y + vd_y * p_length, height), WHITE);
    if (draw_hitbox)
    {
        DrawCircleLines(conv(x, width), conv(y, height), conv(p_length, width), RED);
    }
}

double player_get_v(void)
{
    return sqrt(vx * vx + vy * vy);
}

int player_update(double time)
{
    x = lerp_precise(x, x + vx, time);
    y = lerp_precise(y, y + vy, time);
    x = (x < 0) * 1000 + (x >= 0) * (x % 1000);
    y = (y < 0) * 1000 + (y >= 0) * (y % 1000);
    if (IsKeyDown(KEY_A))
    {
        va -= 0.125;
    }
    else if (IsKeyDown(KEY_D))
    {
        va += 0.125;
    }
    else if (IsKeyDown(KEY_W))
    {
        vx += cos(va) * 2.5;
        vy += sin(va) * 2.5;
        double vx2 = vx * vx;
        double vy2 = vy * vy;
        if (vx2 + vy2 >= MAX_V2)
        {
            double sq = sqrtf(vx2 + vy2);
            vx /= sq;
            vy /= sq;
            vx *= MAX_V;
            vy *= MAX_V;
        }
    }
    if (IsKeyDown(KEY_SPACE))
    {
        return 1;
    }
    return 0;
}

int player_tick(int width, int height, double time)
{
    player_draw(width, height);
    return player_update(time);
}

int player_get_x()
{
    return x;
}
int player_get_y()
{
    return y;
}
float player_get_a()
{
    return va;
}

int player_get_size()
{
    return 5.0 * PLAYER_SIZE;
}

void player_switch_hitbox(void)
{
    draw_hitbox = !draw_hitbox;
}