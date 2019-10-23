#include <stdio.h>
#include <curses.h>

int main()
{
  int key;

  initscr();
  key = getch();
  endwin();
  printf("%d", key);
  return (0);
}
