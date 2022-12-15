#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef void (*fptr)();

void f()
{
  cout << __PRETTY_FUNCTION__ << endl;
}

fptr foo()
{
  cout << __PRETTY_FUNCTION__ << endl;

  return f;
}

int &bar()
{
  static int i;

  return i;
}

class baz {
public:
  baz &operator()() { return *this; }
};

class greater_than {
private:
  int value;
public:
  greater_than(int x) : value(x) {}

  bool operator()(int i) { return i > value; }
};

bool greater_than_70(int i)
{
  return i > 70;
}

class adjust_by {
private:
  int amount;
public:
  adjust_by(int i) : amount(i) {}

  void operator()(int &i) { i += amount; }
};

void print_int(int i)
{
  cout << i << " ";
}

int main(int argc, char *argv[])
{
  int i;
  vector<int> v;
  greater_than gt42(42);
  greater_than gt70(70);
  
  
  for (i = 0; i < 100; i++) {
    v.push_back(i);
  }

  cout << count_if(v.begin(), v.end(), gt42) << endl;
  cout << count_if(v.begin(), v.end(), gt70) << endl;
  cout << count_if(v.begin(), v.end(), greater_than_70) << endl;
  cout << count_if(v.begin(), v.end(), greater_than(-1)) << endl;

  if (gt42(43)) {
    cout << "7 is greater than 42" << endl;
  } else {
    cout << "7 is not greater than 42" << endl;
  }

  for_each(v.begin(), v.end(), adjust_by(25));
  for_each(v.begin(), v.end(), print_int);
  cout << endl;

  v.clear();

  for (i = 0; i < 100; i++) {
    v.push_back(rand() % 1000);
  }
  for_each(v.begin(), v.end(), print_int);
  cout << endl;

  sort(v.begin(), v.end());
  for_each(v.begin(), v.end(), print_int);
  cout << endl;


  v.clear();
  for (i = 0; i < 100; i++) {
    v.push_back(rand() % 1000);
  }
  for_each(v.begin(), v.end(), print_int);
  cout << endl;

  for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    cout << *(it = find_if(it, v.end(), greater_than(500))) << endl;


  /*
  foo()();

  cout << (bar() = 1) << endl;
  cout << bar()++ << endl;
  cout << bar()++ << endl;

  baz b;

  b();
  */
  
  return 0;
}
