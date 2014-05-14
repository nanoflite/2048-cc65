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
  unsigned char i;
  char *s, *d;

  asm("lda #142"); // graphics/uppercase
  asm("jsr $ffd2");
  asm("lda #147"); // clr home
  asm("jsr $ffd2");
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
  char x;
  char y;
  unsigned char value;

  x = 10 * tile->x + 9;
  y =  5 * tile->y + 6;
  value = tile_get_value(tile);
 
  numbers_clear_rect(x, y, 4);

  if ( value != 0 ) {
    numbers_number_xy_condensed( 1 << value, x, y );
  }

}

void screen_draw(void)
{}

void screen_draw_you_won(void)
{
  //cputsxy(10, 10, "YOU WON");
  box("you won");
}

void screen_draw_game_over(void)
{
  //cputsxy(10, 10, "GAME OVER");
  box("game over");
}

bool screen_draw_and_ask_restart(void)
{
  char input;

  // cputsxy(11, 13, "restart y/n?");
  box("restart y/n?"); 

  input = wait_kbhit();
  if ( 'y' == input || 'Y' == input ) {
    return true;
  }
  
  /*
  x = 10 * tile->x + 9;
  y =  5 * tile->y + 6;
  */
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

void screen_title(void)
{}

void screen_reinit(void)
{}
