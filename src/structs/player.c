#include "structs/player.h"
#include <math.h>
#include "raylib.h"
#include "rlgl.h"

#define conv(x, s) (((double)(x) / 1000.0) * ((double)s))

int x = 0;
int y = 0;
double va = 1.1;
double vx = 0;
double vy = 0;

const static double MAX_V = 15.0;
const static double MAX_V2 = 225;

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
    double n_y = -(cos(va) / sin(va));
    const double v_l = sqrt(1 + n_y * n_y);
    const static double p_s = 5.0;
    const static double p_length = 25;
    const static double p_width = 10;
    const static double p_tail = 12.5;
    n_x /= v_l;
    n_y /= v_l;
    DrawLine(conv(x + vd_x * p_length, width), conv(y + vd_y * p_length, height), conv(-vd_x * p_tail + x + n_x * p_width, width), conv(-vd_y * p_tail + y + n_y * p_width, height), WHITE);
    DrawLine(conv(-vd_x * p_tail + x + n_x * p_width, width), conv(-vd_y * p_tail + y + n_y * p_width, height), conv(x, width), conv(y, height), WHITE);
    DrawLine(conv(x, width), conv(y, height), conv(-vd_x * p_tail + x - n_x * p_width, width), conv(-vd_y * p_tail + y - n_y * p_width, height), WHITE);
    DrawLine(conv(-vd_x * p_tail + x - n_x * p_width, width), conv(-vd_y * p_tail + y - n_y * p_width, height), conv(x + vd_x * p_length, width), conv(y + vd_y * p_length, height), WHITE);
}

void player_update()
{
    x += vx;
    y += vy;
    x = (x < 0) * 1000 + (x >= 0) * (x % 1000);
    y = (y < 0) * 1000 + (y >= 0) * (y % 1000);
    if (IsKeyDown(KEY_A))
    {
        va -= 0.075;
    }
    else if (IsKeyDown(KEY_D))
    {
        va += 0.075;
    }
    else if (IsKeyDown(KEY_W))
    {
        vx += cos(va) / 3.5;
        vy += sin(va) / 3.5;
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
}

void player_tick(int width, int height)
{
    player_draw(width, height);
    player_update();
}