#include "utils.h"
#include "game.h"
#include "screen.h"

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

int main(int argc, char *argv[])
{
  char input;
  direction direction;

  screen_title();

  screen_init();

  while (1) {
    screen_reinit();
    game_init(screen_draw_cell);
    screen_draw();
    screen_draw_score();
    while(1) {
      game_draw();   

      if (game_is_finsihed()) {
        if ( game_won() ) {
          screen_draw_you_won();
        } else {
          screen_draw_game_over();
        }
        wait_kbhit();
        break;
      }

      input = wait_kbhit();
      if ( 'q' == input || 'Q' == input ) {
        if (screen_draw_and_ask_restart()) {
          break;
        }
      }

      direction = get_direction(input);
      game_move(direction);
      screen_draw_score();
   
      if (game_moved()) {
        game_add_random_tile();
      }

    }

  }

  return 0;
}
