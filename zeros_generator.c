#include "zeros_generator.h"
#include "polynomial.h"
#include "config.h"


#include <complex.h>
#include <stdlib.h>
#include <stdio.h>


Polynomial new_polynomial(double radius, int zero_count, zero_pattern mode)
{
    double complex* zeros = malloc(zero_count * sizeof(double complex));

    // Nth roots of unity
    for (int i = 0; i < zero_count; i++)
    {
        double complex z = radius * cexp(i * 2 * PI * I / (zero_count));
        printf("Generating root of unity: %f, %f\n", creal(z), cimag(z));
        zeros[i] = z;
    }

    Polynomial polynomial = make_polynomial(zero_count, zeros);


    return polynomial;
}

void free_polynomial(Polynomial *polynomial)
{
    free(polynomial->zeros);
}
