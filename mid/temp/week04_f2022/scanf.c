#include <stdio.h>

int main(int argc, char *argv[])
{
  char c;
  int x, y;
  
  scanf("%c", &c);

  printf("Read a %c\n", c);

  if (c == 'f') {
    scanf(" %d %d", &x, &y);
    printf("Flying to (%d,%d)\n", x, y);
  }
  
  return 0;
}
