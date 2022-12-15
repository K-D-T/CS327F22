#include <stdio.h>
#include <string.h>

struct foo {
  int i;
  float f;
  char s[80];
};

/* A pointer is a variable that hold an address */
void init_foo(struct foo *f)
{
  /*  f->i = 3;*/
  (*f).i = 3;
  f->f = 4.5;
  strcpy(f->s, "Hello World!");
}

void swap_wrong(int i, int j)
{
 int tmp = i;
  i = j;
  j = tmp;

  printf("in swap: i = %d j = %d\n", i, j);
}

void swap_right(int *i, int *j)
{
  int tmp = *i;
  *i = *j;
  *j = tmp;

  printf("in swap: i = %d j = %d\n", *i, *j);
}

int main(int argc, char *argv[])
{
  struct foo f;
  int i, j;
  
  init_foo(&f);

  printf("%d, %f, %s\n", f.i, f.f, f.s);

  i = 0;
  j = 1;

  swap_right(&i, &j);

  printf("in main: i = %d j = %d\n", i, j);

  return 0;
}
