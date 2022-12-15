#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertion_sort(int *a, int n)
{
  int i, j, t;
  
  for (i = 1; i < n; i++) {
    for (t = a[i], j = i - 1; j > -1 && a[j] > t; j--) {
      a[j + 1] = a[j];
    }
    a[j + 1] = t;
  }
}

/* s is size of a single element.  compare is pointer to comparitor */
void generic_insertion_sort(void *v, int n, int s,
                            int (*compare)(void *, void *))
{
  int i, j;
  void *t = malloc(s); /* Space to copy temporary */
  char *a = v; /* char pointer allows byte addressing */
  
  for (i = 1; i < n; i++) {
    for (memcpy(t, &a[i * s], s), j = i - 1;
         j > -1 && compare(&a[j * s], t) > 0;
         j--) {
      memcpy(&a[(j + 1) * s], &a[j * s], s);
    }
    memcpy(&a[(j + 1) * s], t, s);
  }

  free(t);
}

int int_reverse_cmp(void *v1, void *v2)
{
  return *((int *) v2) - *((int *) v1);
}

int strptrcmp(void *v1, void *v2)
{
  return strcmp(*((char **) v1), *((char **) v2));
}

int main(int argc, char *argv[])
{
  int i;
  int a[] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
  char *s[] = {
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
  };

  insertion_sort(a, sizeof (a) / sizeof (a[0]));

  for (i = 0; i < sizeof (a) / sizeof (a[0]); i++) {
    printf("%d ", a[i]);
  }
  printf("\n");

  generic_insertion_sort(a, sizeof (a) / sizeof (a[0]),
                         sizeof (a[0]), int_reverse_cmp);
  
  for (i = 0; i < sizeof (a) / sizeof (a[0]); i++) {
    printf("%d ", a[i]);
  }
  printf("\n");

  qsort(s, sizeof (s) / sizeof (s[0]),
                         sizeof (s[0]), strptrcmp);
  
  for (i = 0; i < sizeof (s) / sizeof (s[0]); i++) {
    printf("%s ", s[i]);
  }
  printf("\n");

  printf("%s\n", bsearch("seven", s, sizeof (s) / sizeof (s[0]),
                         sizeof (s[0]), strptrcmp));

  return 0;
}
