#include <conio.h>

#include "introscreen_data.h"

char wait_kbhit(void)
{
  while(!kbhit()) {};
  return cgetc();
}

void utils_draw_introscreen(char *screen)
{
  char *data;
  unsigned int i;
  
  data = introscreen;
  for(i=0; i<introscreen_len; i++) {
    *screen = *data;
    screen++;
    data++;
  }

}
