#include <stdio.h>

#include <conio.h>

#include "game.h"

void draw_cell(tile *tile)
{
  gotoxy( tile->x << 2, tile->y << 2 );

  if (tile->added) {
    textcolor( COLOR_RED );
  }
  if (tile->moved) {
    textcolor( COLOR_WHITE );
  }
  if ( 0 == tile->value ) {
    puts("    ");
  } else {
    printf("%d", tile->value); 
  }
  textcolor( COLOR_BLACK );

  tile_set_added(tile, false);
  tile_set_moved(tile, false);
}

int main(int argc, char *argv[])
{
  char input;
  direction direction;
  game_init(draw_cell);

  textcolor( COLOR_BLACK );
  clrscr();

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
      default:
        direction = DIR_UNKNOWN;
    }
    game_move(direction);

    if (game_is_finsihed()) {
      break;
    }
    
    if (game_moved()) {
      game_add_random_tile();
    }

  }

  return 0;
}
