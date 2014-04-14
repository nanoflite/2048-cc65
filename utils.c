#include <conio.h>

char wait_kbhit(void)
{
  while(!kbhit()) {};
  return cgetc();
}
