#include <stdio.h>

#include <conio.h>

#include "map.h"
#include "game.h"
#include "characters.h"
#include "map_data.h"

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

int main(int argc, char *argv[])
{
  char input;
  direction direction;

  game_init(draw_cell);
  
  charset_init();
  chars_init();
  draw_screen();

  while(1) {

    game_draw();   
 
    while(!kbhit()) {};

    input = cgetc();
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
      case '?':
        game_dump();
        break;
      default:
        direction = DIR_UNKNOWN;
    }
    game_move(direction);
   
    if (game_moved()) {
      game_add_random_tile();
    }

    if (game_is_finsihed()) {
      break;
    }
 
  }
  
  if ( game_won() ) {
    printf("\nYOU WIN!");
  } else {
    printf("\nGAME OVER");
  }

  return 0;
}
