#ifndef ZEROS_H
#define ZEROS_H

#include "polynomial.h"

typedef enum zero_pattern
{
    NORMAL,
    SPIRAL,
    SPIRAL_INV
} zero_pattern;

Polynomial new_polynomial(double radius,
                   int zero_count,
                   zero_pattern mode);


void free_polynomial(Polynomial* polynomial);


#endif // ZEROS_H
