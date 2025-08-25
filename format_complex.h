#ifndef FORMAT_COMPLEX_H
#define FORMAT_COMPLEX_H
#include <complex.h>
#include <stdlib.h>

void cmpl_to_string(char* buffer, 
                           size_t size, 
                           const double complex* z);
#endif
