#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <conio.h>

#include "tile.h"
#include "game.h"
#include "utils.h"

void screen_init(void)
{
}

void screen_draw_cell(tile *tile)
{
  char x;
  char y;
  unsigned char value;

  x = tile->x << 2;
  y = tile->y << 1;
  value = tile_get_value(tile);

  gotoxy( x, y );
  //if ( value == 0 ) {
  //  puts("    ");
  //} else {
    printf("%d", value);
  //}
}

void screen_draw(void)
{
}

void screen_draw_you_won(void)
{
  cputsxy(10, 10, "YOU WON");
}

void screen_draw_game_over(void)
{
  cputsxy(10, 10, "GAME OVER");
}

bool screen_draw_and_ask_restart(void)
{
  char input;
 
  cputsxy(10, 10, "RESTART Y/N?");
 
  input = wait_kbhit();
  if ( 'y' == input || 'Y' == input ) {
    return true;
  }
 
  return false;
}

void screen_draw_score(void)
{
  gotoxy(0, 20);
  printf("     score: %d", game_score());
  gotoxy(0, 21);
  printf("best score: %d", game_best_score());
}

void screen_title(void)
{
  /*
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
  */
  clrscr();
  puts("2048 pet edition");
  wait_kbhit();
  /*
  textcolor(COLOR_WHITE);
  bordercolor(COLOR_WHITE);
  bgcolor(COLOR_WHITE);
  */
  clrscr();
}

