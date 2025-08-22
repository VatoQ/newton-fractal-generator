#include "polynomial.h"
#include "fractal.h"
//#include "format_complex.h"
#include <complex.h>
//#include <stdio.h>
//#include <stdlib.h>
#include "write_csv.h"

#define N 3
#define QUANTUM 100

int main()
{
    const int X_RESOLUTION = 9 * QUANTUM;
    const int Y_RESOLUTION = 9 * QUANTUM;
    const int MATRIX_SIZE = X_RESOLUTION * Y_RESOLUTION;

    const double X_RANGE = .5;
    const double X_ROOT = -X_RANGE / 2;
    const double Y_ROOT = -X_RANGE / 2;
    double complex zeros[N] = {
        1 + 0 * I,
        -1.054 + 0.97 * I,
        -0.92 - 1 * I,
    };
    Color matrix[MATRIX_SIZE];

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

    //for (int y = 0; y < Y_RESOLUTION; y++)
    //{
    //    for (int x = 0; x < X_RESOLUTION; x++)
    //    {
    //        Color pixel = matrix[x * Y_RESOLUTION + y];
    //        printf("(%d,%d,%d)", pixel.r, pixel.g, pixel.b);
    //    }
    //    printf("\n");
    //}


    if (status == 0)
    {
        write_csv("image_data.csv", matrix, X_RESOLUTION, Y_RESOLUTION);
    }

    return status;
}

