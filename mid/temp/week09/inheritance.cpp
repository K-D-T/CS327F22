#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class shape {
public:
  virtual double area() const = 0; // Equivelant to abstract in Java
                                   // "Pure virtual"
  virtual double perimeter() const = 0;
  virtual ostream &print(ostream &o) const = 0;
  virtual ~shape() {}
};

ostream &operator<<(ostream &o, const shape &s)
{
  return s.print(o);
}

class rectangle : public shape { // extends shape
protected:
  double length, width;
public:
  rectangle(double l, double w)
  {
    length = l;
    width = w;
  }

  virtual double perimeter() const 
  {
    return 2 * (length + width);
  }

  virtual double area() const 
  {
    return length * width;
  }

  virtual ostream &print(ostream &o) const
  {
    return o << "rectangle[" << length << "," << width << "]";
  }
  virtual ~rectangle() {}
};

class circle : public shape {
private:
  double radius;
public:
  circle(double r)
  {
    radius = r;
  }

  double perimeter() const 
  {
    return 2 * M_PI * radius;
  }

  double area() const 
  {
    return M_PI * radius * radius;
  }

  ostream &print(ostream &o) const
  {
    return o << "circle[" << radius << "]";
  }
};

class square : public rectangle {
public:
  square(double s) : rectangle(s, s) // Initialization list
  {
    //    super(s, s); // Java way
  }

  ostream &print(ostream &o) const
  {
    return o << "square[" << width << "]";
  }
};

int main(int argc, char *argv[])
{
  /*
  rectangle r(5,7);
  shape *a[100];
  int i;
  int j;
  
  cout << r << ": area " << r.area() << ", perimeter " << r.perimeter() << endl;

  circle c(4);
  
  cout << c << ": area " << c.area() << ", perimeter " << c.perimeter() << endl;

  square s(9);

  cout << s << ": area " << s.area() << ", perimeter " << s.perimeter() << endl;

  r = square(3);
  
  cout << r << ": area " << r.area() << ", perimeter " << r.perimeter() << endl;

  rectangle *t = &s;

  cout << *t << ": area " << t->area() << ", perimeter " << t->perimeter() << endl;


  //  t = malloc(sizeof (square)); // C way; doesn't call constructor
  t = new square(5);
  cout << *t << ": area " << t->area() << ", perimeter " << t->perimeter() << endl;

  for (i = 0; i < 100; i++) {
    switch ((j = rand() % 3)) {
    case 0:
      a[i] = new rectangle(rand(), rand());
      break;
    case 1:
      a[i] = new square(rand());
      break;
    case 2:
      a[i] = new circle(rand());
      break;
    }
  }
  
  for (i = 0; i < 100; i++) {
    cout << *a[i] << ": area " << a[i]->area() << ", perimeter " << a[i]->perimeter() << endl;
  }

  rectangle &v = s;
  
  cout << v << ": area " << v.area() << ", perimeter " << v.perimeter() << endl;

  delete t;
  for (i = 0; i < 100; i++) {
    delete a[i];
  }
  */  

  vector<shape *> v;
  unsigned i;

  for (i = 0; i < rand(); i++) {
    switch (rand() % 3) {
    case 0:
      v.push_back(new rectangle(rand(), rand()));
      break;
    case 1:
      v.push_back(new square(rand()));
      break;
    case 2:
      v.push_back(new circle(rand()));
      break;
    }
  }
  
  cout << v.size() << endl;
  /*
  for (i = 0; i < v.size(); i++) {
    cout << *v[i] << endl;
  }
  */

  vector<shape *>::iterator vi;

  for (vi = v.begin(); vi != v.end(); vi++) {
    /* "Dereference" iterator to get to the thing inside. *
     * Dereference that, since it's a pointer.            */
    cout << **vi << endl;
  }

  
  return 0;
}
