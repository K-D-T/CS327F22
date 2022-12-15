#include <stdio.h>
#include <string.h>

#include <sys/time.h>


int strcmp327(const char *s1, const char *s2)                                  
{
  /* Works!  But expensive
  if (*s1 < *s2) { // or (s1[0] == s2[0])
    return -1;
  } else if (*s1 > *s2) {
    return 1;
  } else if (!*s1) {
    return 0;
  }
  
  return strcmp327(s1 + 1, s2 + 1);
  */
    
  while (*s1 && (*s1 == *s2)) {
    s1++;
    s2++;
  }
  
  return *s1 - *s2;  
}


int main(int argc, char *argv[])
{
  char foo[] = "Hello!";
  char bar[] = "Hello!";
  int i;
  unsigned long long dif;

  struct timeval start, end;

  //  /* Broken!  Invoking undefined behavior */
  foo[6] = '!';
  bar[6] = '!';

  printf("'%s' '%s'\n", foo, bar);
  //  */

  gettimeofday(&start, NULL);
  for (i = 0; i < 100000000; i++) {
    strcmp327(foo, bar);
  }
  printf("'%s' '%s'\n", foo, bar);
  gettimeofday(&end, NULL);

  dif = (unsigned long long) end.tv_sec * 1000000ULL + end.tv_usec;
  dif -= (unsigned long long) start.tv_sec * 1000000ULL + start.tv_usec;

  printf("%llu us\n", dif);
  
  return 0;
}
