#ifndef CPP_FILE_H
# define CPP_FILE_H

#ifdef __cplusplus

#include <iostream>

using namespace std;

extern "C" {

#else
typedef void ostream;
#endif

ostream *get_cout();
void use_cout(ostream *o, const char *s);

#ifdef __cplusplus
}
#endif

#endif
