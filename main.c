#include <stdio.h>

#include <conio.h>

#include "game.h"

int main(int argc, char *argv[])
{
  char input;
  direction direction;
  game_init();

  while(1) {
    
    clrscr();
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
