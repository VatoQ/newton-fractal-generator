#include "polynomial.h"
#include "fractal.h"
#include "format_complex.h"
#include <complex.h>
#include <stdio.h>

#define N 4

int main()
{
    const int X_RESOLUTION = 16 / 3;
    const int Y_RESOLUTION = 9 / 3;
    const int MATRIX_SIZE = X_RESOLUTION * Y_RESOLUTION;
    const double X_ROOT = -8;
    const double Y_ROOT = -4.5;
    const double X_RANGE = 16.;
    double complex zeros[N] = {
        1 + 0 * I,
        0 + 1 * I,
        -1 + 0 * I,
        0 - 1 * I
    };
    Color* matrix[MATRIX_SIZE];

    Polynomial polynomial = make_polynomial(N, zeros);

    FractalGenerator fractal_generator = make_fractal_generator(
        X_RESOLUTION,
        Y_RESOLUTION,
        X_ROOT,
        Y_ROOT,
        X_RANGE,
        &polynomial
    );

    int status = fractal_generator.generate(&fractal_generator,
                                            matrix);

    for (int y = 0; y < Y_RESOLUTION; y++)
    {
        for (int x = 0; x < X_RESOLUTION; x++)
        {
            printf("%s, ", cmpl_to_string(&matrix[x * Y_RESOLUTION + y]));
        }
        printf("\n");
    }


    return status;
}

