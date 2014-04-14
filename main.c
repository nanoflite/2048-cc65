#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <conio.h>

#include "map.h"
#include "game.h"
#include "characters.h"
#include "map_data.h"
#include "introscreen_data.h"

static void draw_cell(tile *tile)
{
  char x;
  char y;
  unsigned char value;

  x = tile->x + 2;
  y = tile->y + 1;
  value = tile_get_value(tile);

  chars_draw_tile( x, y, value );
}

static void draw_screen(void)
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

static char wait_kbhit(void)
{
  while(!kbhit()) {};
  return cgetc();
}

static void draw_you_won(void)
{
  chars_draw_tile( 3, 2, 18 );
  chars_draw_tile( 4, 2, 19 );
}

static void draw_game_over(void)
{
  chars_draw_tile( 3, 2, 20 );
  chars_draw_tile( 4, 2, 21 );
}

static bool draw_and_ask_restart(void)
{
  char input;
  chars_draw_tile( 3, 2, 22 );
  chars_draw_tile( 4, 2, 23 );
  
  input = wait_kbhit();
  if ( 'y' == input || 'Y' == input ) {
    return true;
  }
  
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

static void draw_score(void)
{
  _draw_score( game_score(), (char*) SCREEN + 40 * 1 + ( 3 * 5 ) - 1 );
  _draw_score( game_best_score(), (char*) SCREEN + 40 * 1 + ( 6 * 5 ) - 1 );
}

direction get_direction(char input)
{
  direction direction;

  switch (input) {
    case 'w':
    case 'W':
      direction = DIR_UP;
      break;
    case 'd':
    case 'D':
      direction = DIR_RIGHT;
      break;
    case 's':
    case 'S':
      direction = DIR_DOWN;
      break;
    case 'a':
    case 'A':
      direction = DIR_LEFT;
      break;
    default:
      direction = DIR_UNKNOWN;
  }

  return direction;
}

void show_title(void)
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

int main(int argc, char *argv[])
{
  char input;
  direction direction;

  show_title();

  charset_init();
  chars_init();

  while (1) {
    game_init(draw_cell);
    draw_screen();
    draw_score();
    while(1) {
      game_draw();   

      if (game_is_finsihed()) {
        if ( game_won() ) {
          draw_you_won();
        } else {
          draw_game_over();
        }
        wait_kbhit();
        break;
      }

      input = wait_kbhit();
      if ( 'q' == input || 'Q' == input ) {
        if (draw_and_ask_restart()) {
          break;
        }
      }

      direction = get_direction(input);
      game_move(direction);
      draw_score();
   
      if (game_moved()) {
        game_add_random_tile();
      }

    }

  }

  return 0;
}
