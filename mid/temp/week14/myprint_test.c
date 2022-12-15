#include <dlfcn.h>
#include <errno.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  void *handle;
  int (*printf)(const char *, ...);

  if (!(handle = dlopen("./libmyprintf.so", RTLD_LAZY))) {
    perror(dlerror());
    return -1;
  }

  if (!(printf = dlsym(handle, "myprintf"))) {
    perror("myprintf");
    return -1;
  }
  
  printf("Hello World!\n");

  dlclose(handle);

  return 0;
}
