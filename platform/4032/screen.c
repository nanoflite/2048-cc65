#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <conio.h>

#include "tile.h"
#include "game.h"
#include "utils.h"
#include "grid.h"

#include "numbers.h"

#include "header_data.h"

#define SCREEN 0x8000

char numbers_source[40*25];

char *number_sources[12];
char *number_destinations[16];

static void block_copy(char from, char to)
{
  #define W 9 
  char x, y;
  char *s, *d;
  
  s = number_sources[from];
  d = number_destinations[to];

  for(y=0;y<4;y++) {
    for(x=0;x<W;x++) {
      *d++ = *s++;
    }
    d += 40 - W;
    s += 40 - W;
  }
  #undef W
}

static void box(const char *text)
{
  char i, x;
  char *s;
  tile *tile;

  numbers_clear_rect( 10 * 1 + 9, 5 * 1 + 6, 4);
  numbers_clear_rect( 10 * 2 + 9, 5 * 1 + 6, 4);

  tile = grid_get(1, 1);
  tile_set_needs_drawing(tile, true);
  tile = grid_get(1, 2);
  tile_set_needs_drawing(tile, true);

  s = (char*) SCREEN + 10 * 40 + 20;
  *s = 0x71;
  s += 40;
  for(i=0;i<4;i++){
    *s = 0x20;
    s += 40;
  }
  *s = 0x72;
  
  x = 20 - strlen(text) / 2;
  cputsxy(x, 13, text);
}

void screen_init(void)
{
}

void screen_reinit(void)
{
  unsigned char i;
  char *s, *d;

  clrscr();

  s = (char *)SCREEN;
  d = header;
  for(i=0;i<200;i++) {
    *s = *d;
    s++;
    d++;
  }

  for(i=0;i<3;i++) {
    numbers_hline(0, 10 + 5 * i, 40 );
    numbers_vline( 10 + i * 10, 6, 19 );
  }
}

void screen_draw_cell(tile *tile)
{
  block_copy( tile_get_value(tile), ( tile->y << 2 ) + tile->x );
}

void screen_draw(void)
{}

void screen_draw_you_won(void)
{
  box("you won");
}

void screen_draw_game_over(void)
{
  box("game over");
}

bool screen_draw_and_ask_restart(void)
{
  char input;

  box("restart y/n?"); 

  input = wait_kbhit();
  if ( 'y' == input || 'Y' == input ) {
    return true;
  }
  
  numbers_vline( 10 + 1 * 10, 6, 19 );
  numbers_clear_rect( 10 * 1 + 9, 5 * 1 + 6, 4);
  numbers_clear_rect( 10 * 2 + 9, 5 * 1 + 6, 4);
  return false;
}

void screen_draw_score(void)
{
  unsigned int score;

  score = game_score();
  gotoxy(0, 1);
  cprintf("%05d", score);

  score = game_best_score();
  gotoxy(35, 1);
  cprintf("%05d", score);

}

static void prepare(void)
{
  char i, x, y;
  char *s;

  // Generate numbers in shadow space.
  s = numbers_source;
  for(y=0;y<25;y++) {
    for(x=0;x<40;x++) {
      *s = 0x20;
      s++;
    }
  }

  numbers_set_screen(numbers_source);

  for(i=0;i<12;i++) {
    x = i & 0x03;
    y = ( i & ~0x03 ) >> 2;

    number_sources[i] = numbers_source + ( 5 + y  * 5 ) * 40 + 10 * x + 1;

    x = 9 + x * 10;
    y = 5 + y * 5;

    if ( i > 0 ) {
      numbers_number_xy_condensed( 1 << i, x, y );
    }

  }

  i = 0;
  for(y=0;y<4;y++) {
    for(x=0;x<4;x++) {
      number_destinations[i] = (char*) SCREEN + ( 6 + y * 5 ) * 40 + 10 * x + 1;
      i++;
    }
  }

  numbers_set_screen((unsigned char*) SCREEN);

  wait_kbhit();
}

void screen_title(void)
{
  char *screen;

  asm("lda #142"); // graphics/uppercase
  asm("jsr $ffd2");
  asm("lda #147"); // clr home
  asm("jsr $ffd2");

  screen  = (unsigned char*) SCREEN; // Still standard screen address here;
  utils_draw_introscreen(screen);
  
  prepare();

  wait_kbhit();
}


