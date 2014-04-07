#include <conio.h>

#include "map.h"
#include "chars_data.h"
#include "tiles_data.h"
#include "attribs_data.h"

#define CPU_REG_1  ((unsigned char*) 0x0001)
#define RAM_CHARSET ((unsigned char*) 0x8800)
#define SCREEN ((unsigned char*) 0x8000)
#define COLOR ((unsigned char*) 0xD800)

//TODO: Choose correct video bank and adresses
//edit c64.cfg so program does not overlap videobank 

void charset_init(void)
{
    unsigned int i;
    char *from, *to;

    // copy charset to RAM
    from = chars;
    to = RAM_CHARSET;
    for( i=0; i < chars_len; i++ ) {
      *to++ = *from++;
    }

    // copy correct colors to the regs

    *(&VIC.addr) = (*(&VIC.addr) & 0xf0) | 0x0c; // Switch char ram addr to 0x3000
}

void charset_show(void)
{
  char *screen;
  int c;

  screen = SCREEN;
  
  for(c=0;c<=255;c++) {
    *screen++ = (char) c;
  }
}

void tiles_draw(unsigned char tile_nr, unsigned char x, unsigned char y)
{
  unsigned char i, j;
  char *tile_ptr;
  char *screen;
  char *color;
  char attribute;

  tile_ptr = tiles + tile_nr * 25;
  screen = SCREEN + y * 40 + x;
  color = COLOR + y * 40 + x;
  attribute = attribs[tile_nr];

  for ( i=0; i<5; i++ ) {
    for ( j=0; j<5; j++ ) {
      *screen = *tile_ptr;
      *color = attribute; 
      screen++;
      color++;
      tile_ptr++;
    }
    screen += 40 - 5;
    color += 40 - 5;
  }
}
