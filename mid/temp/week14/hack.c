#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>

void *handle;

__attribute__((constructor)) void init()
{
  if (!(handle = dlopen("libc.so.6", RTLD_LAZY))) {
    perror(dlerror());

    exit(1);
  }
}

__attribute__((destructor)) void deinit()
{
  dlclose(handle);
}

int printf(const char *format, ...)
{
  int (*p)(const char *, ...);

  p = dlsym(handle, "printf");

  p("Goodbye cruel world!\n");
}

int puts(const char *s)
{
  int (*p)(const char *);

  p = dlsym(handle, "puts");

  p("Goodbye cruel world!\n");
}
