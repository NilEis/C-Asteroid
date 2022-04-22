#ifndef PLAYER_H
#define PLAYER_H

void player_init();

void player_draw(int width, int height);

int player_update(double time);

int player_tick(int width, int height, double time);

int player_get_x();

int player_get_y();

double player_get_v(void);

float player_get_a();

int player_get_size();

void player_switch_hitbox(void);

#endif // PLAYER_H
