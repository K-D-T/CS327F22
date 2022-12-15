#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
  int i;
  
  if (argc == 1) {
    printf("Hello World!\n");
  } else {
    for (i = 1; i < argc; i++) {
      if (!strcmp(argv[i], "Putin" /* Same as == 0 */)) {
        printf("Goodbye Putin!\n");
      } else {
        printf("Hello %s!\n", argv[i]);
      }
    }
  }

  return 0;
}
