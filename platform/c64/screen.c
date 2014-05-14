#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <conio.h>

#include "tile.h"
#include "map.h"
#include "characters.h"
#include "map_data.h"
#include "introscreen_data.h"
#include "game.h"
#include "utils.h"
#include "grid.h"

void screen_draw_cell(tile *tile)
{
  char x;
  char y;
  unsigned char value;

  x = tile->x + 2;
  y = tile->y + 1;
  value = tile_get_value(tile);

  chars_draw_tile( x, y, value );
}

void screen_draw(void)
{
  char i;
  char j;
  char k;
  char tile;

  k = 0;
  for(i=0;i<5;i++) {
    for(j=0;j<8;j++) {
      tile = map[k];
      chars_draw_tile( j, i, tile );
      k++;
    }
  }
}

void screen_draw_you_won(void)
{
  chars_draw_tile( 3, 2, 18 );
  chars_draw_tile( 4, 2, 19 );
}

void screen_draw_game_over(void)
{
  chars_draw_tile( 3, 2, 20 );
  chars_draw_tile( 4, 2, 21 );
}

bool screen_draw_and_ask_restart(void)
{
  char input;
  tile *tile;

  chars_draw_tile( 3, 2, 22 );
  chars_draw_tile( 4, 2, 23 );
  
  input = wait_kbhit();
  if ( 'y' == input || 'Y' == input ) {
    return true;
  }

  chars_draw_tile( 3, 2, 0 );
  chars_draw_tile( 4, 2, 0 );

  tile = grid_get(1, 1);
  tile_set_needs_drawing(tile, true);
  tile = grid_get(1, 2);
  tile_set_needs_drawing(tile, true);
  
  return false;
}

static void _draw_score(unsigned int score, char *screen)
{
  #define SCREEN 0x8000

  int i;
  char string[8];
 
  itoa(score, string, 10);
  for(i=strlen(string)-1;i>=0;i--) {
    *screen = 219 - '0' + string[i];
    screen--;
  }
}

void screen_draw_score(void)
{
  _draw_score( game_score(), (char*) SCREEN + 40 * 1 + ( 3 * 5 ) - 1 );
  _draw_score( game_best_score(), (char*) SCREEN + 40 * 1 + ( 6 * 5 ) - 1 );
}

void screen_title(void)
{
  char *data;
  unsigned int i;
  char *screen;
  
  screen  = (unsigned char*) 0x0400; // Still standard screen address here;
  *(unsigned char *)0xd018 = 0x15; // Switch to uppercase charset
  data = introscreen;
  for(i=0; i<introscreen_len; i++) {
    *screen = *data;
    screen++;
    data++;
  }
  wait_kbhit();
  textcolor(COLOR_WHITE);
  bordercolor(COLOR_WHITE);
  bgcolor(COLOR_WHITE);
  clrscr();
}

void screen_init(void)
{
  charset_init();
  chars_init();
}

void screen_reinit(void)
{}
