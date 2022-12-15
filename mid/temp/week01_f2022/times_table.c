#include <stdio.h>

void populate_table(int table[10][10])
{
  int i, j;

  for (j = 1; j <= 10; j++) {
    for (i = 1; i <= 10; i++) {
      table[j - 1][i - 1] = i * j;
    }
  }
}

void print_table(int table[10][10])
{
  int i, j;

  for (j = 0; j < 10; j++) {
    for (i = 0; i < 10; i++) {
      printf("%3d ", table[j][i]);
    }
    printf("\n");
  }
}

int main(int argc, char *argv[])
{
  int t[10][10];
  //int [][] t = new int [10][10];   //Java

  populate_table(t);

  print_table(t);
  
  return 0;
}
