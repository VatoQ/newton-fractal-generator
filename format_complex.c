#include "format_complex.h"
#include <complex.h>
#include <math.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>


#define _NUM_LEN_ 20


void cmpl_to_string(char* buffer,
                           size_t size,
                           const double complex* z)
{
    double a = creal(*z);
    double b = cimag(*z);

    char a_char[_NUM_LEN_];
    snprintf(a_char, _NUM_LEN_, "%.6g", a);

    char b_char[_NUM_LEN_];
    snprintf(b_char, _NUM_LEN_, "%.6g", fabs(b));

    snprintf(buffer, size, "%s %c %si", a_char, (b < 0 ? '-' : '+'), b_char);
}
