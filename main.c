#include <stddef.h>
#define _POSIX_C_SOURCE 199309L
#include "color.h"
#include "polynomial.h"
#include "fractal.h"
#include "write_csv.h"
#include "zeros_generator.h"

#include <time.h>
#include <complex.h>
#include <stdio.h>
#include <stdlib.h>

#define N 7
#define QUANTUM 500

int main()
{
    const int X_RESOLUTION = 9 * QUANTUM;
    const int Y_RESOLUTION = 9 * QUANTUM;
    const int MATRIX_SIZE = X_RESOLUTION * Y_RESOLUTION;

    const double X_RANGE = 4;
    const double X_ROOT = -X_RANGE / 2;
    const double Y_ROOT = -X_RANGE / 2;
    const double RADIUS = 1.5;

    const size_t FLOP_PER_ITER = 30;
    const size_t MIN_FLOP = (FLOP_PER_ITER + 1) * X_RESOLUTION * Y_RESOLUTION;
    const size_t MAX_FLOP = (FLOP_PER_ITER + 50) * X_RESOLUTION * Y_RESOLUTION;


    

    Polynomial polynomial = new_polynomial(RADIUS, N, NORMAL);

    FractalGenerator fractal_generator = make_fractal_generator(
        X_RESOLUTION,
        Y_RESOLUTION,
        X_ROOT,
        Y_ROOT,
        X_RANGE,
        &polynomial
    );

    Color* matrix = malloc(MATRIX_SIZE * sizeof(Color));

    double seconds;
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);

    int status = fractal_generator.generate(&fractal_generator,
                                            matrix);

    clock_gettime(CLOCK_MONOTONIC, &end);

    

    seconds = ((double)end.tv_sec - (double)start.tv_sec) +
        ((double)end.tv_nsec - (double)start.tv_nsec) / 1.0e9;

    double flops_min = (double) MIN_FLOP / seconds;
    double flops_max = (double) MAX_FLOP / seconds;
    // printf("\tMissed zeros: %d\n", fractal_generator.count_zero_misses);
    // double ratio = (double)fractal_generator.count_zero_misses / MATRIX_SIZE;
    // Printf("\tTotal data points: %d\n", MATRIX_SIZE);
    // Printf("\tRatio of misses: %f\n", ratio);

    free_fractal(&fractal_generator);
    free_polynomial(&polynomial);


    if (status == 0)
    {
        write_csv("image_data.csv", matrix, X_RESOLUTION, Y_RESOLUTION);
    }

    free(matrix);

    printf("Elapsed time during generation: %f\n", seconds);
    printf("Min GFLOPs: %f\n", flops_min / 1000000000);
    printf("Max GFLOPs: %f\n", flops_max / 1000000000);

    return status;
}

