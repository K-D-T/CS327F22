#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
  srand(time(NULL));

  printf("%d\n", rand());
  printf("%d\n", rand());
  printf("%d\n", rand());
  printf("%d\n", rand());
  printf("%d\n", rand());

  printf("%d\n", RAND_MAX);

  printf("%d\n", (rand() % 19) + 1);

  printf("%f\n", (float) rand());
  printf("%f\n", (float) rand());
  printf("%f\n", (float) rand());
  printf("%f\n", (float) rand());
  printf("%f\n", (float) rand());

  printf("%f\n", rand() / (float) RAND_MAX);
  printf("%f\n", rand() / (float) RAND_MAX);
  printf("%f\n", rand() / (float) RAND_MAX);
  printf("%f\n", rand() / (float) RAND_MAX);
  printf("%f\n", rand() / (float) RAND_MAX);
  
  return 0;
}
