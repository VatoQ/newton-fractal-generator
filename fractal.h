#ifndef FRACTAL_H
#define FRACTAL_H

#include "polynomial.h"
#include "color.h"

typedef struct
{
    double complex zero;
    Color color;
} ColorDict;

typedef struct fractal {
    double x_range, y_range;
    double x_root, y_root;

    int x_resolution, y_resolution;

    double  stepsize;

    int matrix_size;

    ColorDict* zero_colors;

    Polynomial* polynomial;

    int (*generate)(struct fractal* self,
                    Color* result);


} FractalGenerator ;

FractalGenerator make_fractal_generator(int x_resolution,
                                        int y_resolution,
                                        double x_root,
                                        double y_root,
                                        double x_range,
                                        Polynomial* polynomial);

#endif // FRACTAL_H
