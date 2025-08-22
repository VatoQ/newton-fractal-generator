#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H


#include <complex.h>

typedef struct poly {
    int zero_count;
    double complex* zeros;
    double complex (*exec)(struct poly* polynomial, double complex z);
    double complex (*get_zero)(struct poly* polynomial, double complex z, int* stepcount);

} Polynomial ;


Polynomial make_polynomial(int zero_count, double complex* zeros);

#endif //POLYNOMIAL_H
