#ifndef PLAYER_H
#define PLAYER_H

void player_init();

void player_draw(int width, int height);

int player_update();

int player_tick(int width, int height);

int player_get_x();

int player_get_y();

float player_get_a();


#endif // PLAYER_H
