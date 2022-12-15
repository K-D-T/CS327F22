#include <dlfcn.h>
#include <stdio.h>
#include <errno.h>

void *handle;

__attribute__((constructor)) // GNU Extention -- Not standard C
void init()
{
  handle = dlopen("libc.so.6", RTLD_LAZY);
}

__attribute__((destructor))
void destroy()
{
  dlclose(handle);
}

int puts(const char *s)
{
  int (*libc_puts)(const char *);

  if (!(libc_puts = dlsym(handle, "puts"))) {
     
  }

  libc_puts("im in ur library\ncorrupting your bitz!\n");
  
  libc_puts(s);
}
