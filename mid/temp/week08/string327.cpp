#include <iostream>
#include <cstdlib> //C++ sanitized stdlib.h
#include <cstring>

using namespace std;

class string327 {
private:
  char *s;

public:
  string327()                    // Default constructor
  {
    s = strdup("");
  }

  string327(const char *s)       // Constructor
  {
    this->s = strdup(s);
  }

  string327(const string327 &s)  // Copy constroctur
  {
    this->s = strdup(s.s);
  }

  ~string327()                   // Destructor
  {
    free(s);
  }

  int length() const
  {
    return strlen(s);
  }

  const char *c_str() const
  {
    return s;
  }
  
  string327 substring(int start, int length) const
  {
    string327 tmp;

    free(tmp.s);
    tmp.s = strndup(s + start, length);
    
    return tmp;
  }
                                                    // Trailing const tells 
  string327 operator+(const string327 &s) const     // compiler that method
  {                                                 // does not change this
    string327 out;

    out.s = (char *) realloc(out.s, strlen(this->s) + strlen(s.s) + 1);
    strcat(out.s, this->s);
    strcat(out.s, s.s);

    return out;
  }
  
  string327 operator+=(const string327 &s)
  {
    this->s = (char *) realloc(this->s, strlen(this->s) + strlen(s.s) + 1);
    strcat(this->s, s.s);

    return *this;
  }

  string327 operator+=(const char *s)
  {
    this->s = (char *) realloc(this->s, strlen(this->s) + strlen(s) + 1);
    strcat(this->s, s);

    return *this;    
  }

  string327 operator=(const string327 &s)
  {
    free(this->s);
    this->s = strdup(s.s);

    return *this;
  }
  
  string327 operator=(const char *s)
  {
    free(this->s);
    this->s = strdup(s);

    return *this;
  }
  
  char &operator[](int i)
  {
    return s[i];
  }
  
  bool operator>(const string327 &s) const
  {
    return strcmp(this->s, s.s) > 0;
  }
  
  bool operator<(const string327 &s) const
  {
    return strcmp(this->s, s.s) < 0;
  }

  bool operator>=(const string327 &s) const
  {
    return strcmp(this->s, s.s) >= 0;
  }

  bool operator<=(const string327 &s) const
  {
    return strcmp(this->s, s.s) <= 0;
  }

  bool operator==(const string327 &s) const 
  {
    return strcmp(this->s, s.s) == 0;
  }

  bool operator!=(const string327 &s) const
  {
    return strcmp(this->s, s.s) != 0;
  }

  friend std::istream &operator>>(std::istream &o, const string327 &s);
};

std::ostream &operator<<(std::ostream &o, const string327 &s)
{
  return o << s.c_str();
}

/* This function is buggy; feel free to fix it offline */
/* As written, essentially implements gets()           */
//Friend
std::istream &operator>>(std::istream &i, const string327 &s)
{
  return i >> s.s;
}


int main(int argc, char *argv[])
{
  string327 s;

  cout << s << endl;

  s = "Hello World";

  cout << s << endl;

  string327 t = "Hello world";

  cout << (s > t ? s : t) << endl;

  /*
  cin >> t;
  cout << t << endl;
  */

  t = s.substring(4, 3);
  cout << t << endl;
  cout << t[2] << endl;
  
  return 0;
}
