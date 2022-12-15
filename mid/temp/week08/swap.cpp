#include <iostream>

using namespace std;

void c_swap(int *x, int *y)
{
  int tmp = *x;
  *x = *y;
  *y = tmp;
}

void cpp_swap(int &x, int &y)
{
  int tmp = x;
  x = y;
  y = tmp;
}

int main(int argc, char *argv[])
{
  int x = 7;
  int y = 19;

  c_swap(&x, &y);

  cout << "x = " << x << ", y = " << y << endl;
  
  cpp_swap(x, y);

  cout << "x = " << x << ", y = " << y << endl;
  
  return 0;
}
