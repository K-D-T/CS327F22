#include <iostream>

using namespace std;

class A {
public:
  A() { cout << "Constructing an A" << endl; }
  A(const A &a) { cout << "Copying an A" << endl; }

  virtual ~A() { cout << "Destroying an A" << endl; }
  void print() { cout << "A" << endl; }
};

class B : virtual public A {
public:
  B() : A() { cout << "Constructing an B" << endl; }
  B(const B &b) { cout << "Copying a B" << endl; }

  virtual ~B() { cout << "Destroying a B" << endl; }
  void print() { cout << "B" << endl; }
};

class C : virtual public A {
public:
  C() { cout << "Constructing an C" << endl; }
  C(const C &c) { cout << "Copying a C" << endl; }

  virtual ~C() { cout << "Destroying a C" << endl; }
  void print() { cout << "C" << endl; }
};

class D : public B, public C {
public:
  D() { cout << "Constructing an D" << endl; }
  D(const D &d) { cout << "Copying a D" << endl; }

  virtual ~D() { cout << "Destroying a D" << endl; }
  void print() { cout << "D" << endl; }
};

int main(int argc, char *argv[])
{
  D d;

  d.print();

  d.B::print();
  d.C::print();
  d.B::A::print();
  d.C::A::print();
  d.A::print();
  
  //  ((D) d).A::print();
  //  d.B::A::print();  //Why doesn't this work?
  
  return 0;
}
