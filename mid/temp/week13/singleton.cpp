#include <iostream>

using namespace std;

//Globals declared static tells the linker not to export these symbols from
//the compilation unit (file).
static int foo;

static void bar()
{
  //Static local variables keep their value accross calls
  static int i = 0;
  
  cout << foo << " " << ++i << endl;
}

class singleton {
private:
  int i;

  static singleton *the_instance;
  
  singleton() { cout << "Constructing a singleton" << endl; i = 0; }
  singleton(const singleton &s) { cout << "Copying a singleton" << endl; }
public:
  static singleton *get_instance();
  static singleton &get_reference();
  void increment() { ++i; }
  ostream &print(ostream &o) { return o << i; }
};

ostream &operator<<(ostream &o, singleton *s)
{
  return s->print(o);
}

singleton *singleton::get_instance()
{
  if (!the_instance) {
    the_instance = new singleton;
  }

  return the_instance;
}

singleton &singleton::get_reference()
{
  if (!the_instance) {
    the_instance = new singleton;
  }

  return *the_instance;
}

singleton *singleton::the_instance = NULL;

// With private copy constructor, this function cannot be called.
void baz (singleton s)
{
}

int main(int argc, char *argv[])
{
  singleton *s;

  s = singleton::get_instance();
  s = singleton::get_instance();

  cout << s << endl;
  s->increment();
  cout << s << endl;

  cout << singleton::get_instance() << endl;
  singleton::get_instance()->increment();
  cout << singleton::get_instance() << endl;

  cout << &singleton::get_reference() << endl;

  singleton &r = singleton::get_reference();

  r.increment();

  cout << &r << endl;
  
  return 0;
}
