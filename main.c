#include <stdio.h>

#include <conio.h>

#include "game.h"

char drawn = 0;

void draw_cell(tile *tile)
{
  char x;
  char y;
  unsigned int value;

  value = tile_get_value(tile);

  x = tile->x << 2;
  y = tile->y << 2;
  gotoxy( x, y );

  if (tile_added(tile)) {
    textcolor( COLOR_RED );
  }

  if (tile_moved(tile)) {
    textcolor( COLOR_WHITE );
  }

  if ( 0 == value ) {
    puts("    ");
  } else {
    printf("%d", value);
  }

  textcolor( COLOR_BLACK );
  
  /*
  gotoxy(20, tile->y * 4 + tile->x);
  printf("x:%d, y:%d, v:%d, d:%d\n", tile->x, tile->y, tile->value, tile_dirty(tile));
  drawn++;
  gotoxy(0, 20);
  printf("%d", drawn);
  */
}

int main(int argc, char *argv[])
{
  char input;
  direction direction;
  game_init(draw_cell);

  textcolor( COLOR_BLACK );
  clrscr();

  while(1) {

    clrscr();
    drawn=0;
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
