#include "format_complex.h"
#include <complex.h>
#include <math.h>
#include <string.h>
#include <stdio.h>


#define _NUM_LEN_ 20


const char* cmpl_to_string(double complex* z)
{
    double a = creal(*z);
    double b = cimag(*z);

    char a_char[_NUM_LEN_];
    snprintf(a_char, _NUM_LEN_, "%.6g", a);
    //char* number = "";
    //
    static char number[3 * _NUM_LEN_ + 10];
    number[0] = '\0';

    strcat(number, a_char);


    if (b < 0)
    {
        strcat(number, " - ");
    }
    else
    {
        strcat(number, " + ");
    }

    b = fabs(b);

    char b_char[_NUM_LEN_];

    snprintf(b_char, _NUM_LEN_, "%.6g", b);

    strcat(number, b_char);


    strcat(number, "i");


    return number;
}
