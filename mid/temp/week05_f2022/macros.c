#include <stdio.h>

#define FOO 3 // Value-type macro

// Function-type macro
#define min(x, y) (x < y ? x : y)

#define max(x, y) ({ \
  typeof (x) _x = x; \
  typeof (y) _y = y; \
  _x > _y ? _x : _y; \
})

int really_expensive_function()
{
}

int other_really_expensive_function()
{
}

int func_with_side_effect()
{
}

#define tostring(s) #s

struct lu_entry {
  char *name;
  int (*func)();
}

#define lu_table_entry(name) { #name, name }
  
struct lu_entry table[] = {
  lu_table_entry(foo),
  lu_table_entry(bar),
  lu_table_entry(baz),
};

int lu_cmp(const void *v1, const void *v2)
{
  return strcmp(((lu_entry *) v1)->name, ((lu_entry *) v2)->name);
}


lu_entry tmp = { "name", NULL }
((lu_entry *)bsearch(tmp, table, other parameters...))->func();

#define concat(foo) bar_ ## foo

int main(int argc, char *argv[])
{

  printf("%d\n", FOO);

  printf("%d\n", min(3.14, 1.41));
 
  printf("%d\n", min(really_expensive_function(),
                     other_really_expensive_function()));
  
  printf("%d\n", max(really_expensive_function(),
                     other_really_expensive_function()));
  
  printf("%s\n", tostring(foo));

  concat(baz);
  
  return 0;
}
