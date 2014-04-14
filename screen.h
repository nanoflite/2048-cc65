#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "tile.h"

void screen_draw_cell(tile *tile);
void screen_draw_you_won(void);
void screen_draw_game_over(void);
bool screen_draw_and_ask_restart(void);
void screen_title(void);
void screen_init(void);
void screen_draw(void);
void screen_draw_score(void);

#endif
