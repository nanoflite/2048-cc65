#include <stdio.h>

#include <conio.h>

#include "map.h"
#include "game.h"
#include "characters.h"
#include "map_data.h"

char drawn = 0;

const char *values[] = {
  "    ",
  " 2  ",
  " 4  ",
  " 8  ",
  " 16 ",
  " 32 ",
  " 64 ",
  "128 ",
  "256 ",
  "512 ",
  "1024",
  "2048"
};

const char pos_x[] = {
  1 + 0 * 6,
  1 + 1 * 6,
  1 + 2 * 6,
  1 + 3 * 6
};

const char pos_y[] = {
  1 + 0 * 6,
  1 + 1 * 6,
  1 + 2 * 6,
  1 + 3 * 6
};

static void draw_cell(tile *tile)
{
  char x;
  char y;
  unsigned char value;
  const char *s;


  if (tile_added(tile)) {
    textcolor( COLOR_RED );
  }

  if (tile_moved(tile)) {
    textcolor( COLOR_WHITE );
  }
  
  x = pos_x[tile->x];
  y = pos_y[tile->y];
  value = tile_get_value(tile);
  s = values[value];
  cputsxy( x, y, s );

  textcolor( COLOR_BLACK );
 
  /* 
  gotoxy(20, tile->y * 4 + tile->x);
  printf("x:%d, y:%d, v:%d, d:%d\n", tile->x, tile->y, tile->value, tile_dirty(tile));
  drawn++;
  gotoxy(0, 20);
  printf("%d", drawn);
  */
}

static void draw_grid(void)
{
  char i;
  #define w (4*6)
  cputcxy( 0, 0, '+' );
  cputcxy( 0, w, '+' );
  cputcxy( w, 0, '+' );
  cputcxy( w, w, '+' );
  for(i=1;i<w-1;i++) {
    cputcxy(   i,   0, '-' );   
    cputcxy( w-i,   0, '-' );   
    cputcxy(   0,   i, '-' );   
    cputcxy(   0, w-i, '-' );   
  }
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

  charset_init();
  chars_init();
  draw_screen();

  while(!kbhit()) {};

  game_init(draw_cell);

  textcolor( COLOR_BLACK );
  clrscr();
  draw_grid();

  while(1) {

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
