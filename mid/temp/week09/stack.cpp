#include <iostream>
#include <string>

using namespace std;

template <class T>
T mymin(T x, T y)
{
  return x < y ? x : y;
}

template <class T>
class stack
{
private:
  class stack_node {
  public:
    stack_node *prev;
    T data;

    stack_node(T t) : prev(0), data(t) {}
    stack_node(T t, stack_node *s) : prev(s), data(t) {}
  };

  stack_node *bottom, *top;
  int stack_size;

public:
  stack() : bottom(0), top(0), stack_size(0) {}
  stack(T t) : bottom(new stack_node(t)), top(bottom), stack_size(1) {}
  ~stack()
  {
    stack_node *n;
    while (top) {
      n = top;
      top = top->prev;
      delete n;
    }
    // Unnecessary - Here for completeness
    bottom = 0;
    stack_size = 0;
  }
  void push(T t)
  {
    top = new stack_node(t, top);
    if (!bottom) {
      bottom = top;
    }
    stack_size++;
  }
  T pop()
  {
    if (!stack_size) {
      throw "Attempt to pop an empty stack";
    }
    T tmp = top->data;
    stack_node *n = top;
    top = top->prev;
    delete n;
    stack_size--;

    if (!top) {
      bottom = 0;
    }

    return tmp;
  }
  T peek()
  {
    if (!stack_size) {
      throw "Attempt to peek an empty stack";
    }
    return top->data;
  }
  int size()
  {
    return stack_size;
  }
};

int main(int argc, char *argv[])
{
  /*
  cout << mymin(3,4) << endl;
  cout << mymin(3.5,4.9) << endl;
  cout << mymin("bar","foo") << endl; // Comparing addresses
  cout << mymin(string("bar"),string("foo")) << endl;
  */

  stack<int> s;
  int i;

  for (i = 0; i < 10; i++) {
    s.push(i);
  }
  cout << s.size() << endl;
  for (i = 0; i < 10; i++) {
    cout << s.pop() << endl;
  }
  cout << s.size() << endl;

  for (i = 0; i < 10; i++) {
    s.push(i);
  }
  cout << s.size() << endl;
  try {
    while (1) {
      cout << s.pop() << endl;
    }
  }
  catch (int i) {
    cerr << i << endl;
  }
  /*
  catch (const char *s) {
    cerr << s << endl;
  }
  */
  /*
  catch (...) {
    cout << "Caught an exception" << endl;
  }
  */  
  return 0;
}
