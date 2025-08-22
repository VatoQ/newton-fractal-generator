#include "fractal.h"
#include "format_complex.h"
#include "polynomial.h"
#include "config.h"

#include <math.h>
#include <complex.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef PI
#define PI 3.1415926535897932
#endif // PI
#ifndef TRIG_SCALAR
#define TRIG_SCALAR 127.5
#endif // TRIG__SCALAR

void _init_zeros(FractalGenerator* self)
{
    self->zero_colors = malloc(
        self->polynomial->zero_count * sizeof(ColorDict));

    if (!self->zero_colors) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }



    for (int i = 0; i < self->polynomial->zero_count; i++)
    {
        double x = (double)i * 2. * PI /
            ((double)self->polynomial->zero_count);

        uint8_t r = (uint8_t)(TRIG_SCALAR * cos(x) + TRIG_SCALAR);
        uint8_t g = (uint8_t)(TRIG_SCALAR * sin(x) + TRIG_SCALAR);
        uint8_t b = (uint8_t)(2 * TRIG_SCALAR * sin(2 * x) * sin(2 * x));

        ColorDict color_dict = {
            self->polynomial->zeros[i],
            { r, g, b }
        };
        printf("Generate color: rgb(%d,%d,%d)\n", r, g, b);
        self->zero_colors[i] = color_dict;
    }
}

void _dim_color(Color* pixel, int stepcount)
{
    double decay = exp(-(double)stepcount * (double)stepcount / (STEPCOUNT_MAX * DECAY_FACTOR));
    //printf("\t\tDimming color by: %f\n", decay);
    pixel->r = (uint8_t)(decay * pixel->r);
    pixel->g = (uint8_t)(decay * pixel->g);
    pixel->b = (uint8_t)(decay * pixel->b);

}

Color _get_color(FractalGenerator* self, double complex z)
{
    int stepcount = 0;
    double complex zero = self->polynomial->get_zero(self->polynomial,
                                                     z,
                                                     &stepcount);
    if (stepcount == 0)
    {
        stepcount = STEPCOUNT_MAX;
    }

    //printf("\tstepcount: %d", stepcount);
    
    Color result = { 0, 0, 0};
    for (int i = 0; i < self->polynomial->zero_count; i++)
    {
        if (cabs(zero - self->polynomial->zeros[i]) < 1e-8)
        {
            //printf("\tFound zero %s at %d\n", cmpl_to_string(&zero), i);
            result = self->zero_colors[i].color;
            _dim_color(&result, stepcount);
            break;
        }
    }

    return result;
}


int _fractal_generate(FractalGenerator* self,
                      Color* result)
{
    double a = self->x_root;
    double b = self->y_root;

    for (int x = 0; x < self->x_resolution; x++)
    {
        for (int y = 0; y < self->y_resolution; y++)
        {
            double complex z = a + b * I;
            b += self->stepsize;
            Color pixel = _get_color(self, z);
            result[y * self->x_resolution + x] = pixel;
        }
        b = self->y_root;
        a += self->stepsize;
    }
    return 0;
}

FractalGenerator make_fractal_generator(int x_resolution,
                                        int y_resolution,
                                        double x_root,
                                        double y_root,
                                        double x_range,
                                        Polynomial* polynomial)
{
    FractalGenerator fractal_generator;
    fractal_generator.x_resolution = x_resolution;
    fractal_generator.y_resolution = y_resolution;
    fractal_generator.x_root = x_root;
    fractal_generator.y_root = y_root;
    fractal_generator.x_range = x_range;
    fractal_generator.stepsize = x_range / (double)x_resolution;
    fractal_generator.y_range = fractal_generator.stepsize * y_resolution;
    fractal_generator.matrix_size = x_resolution * y_resolution;
    fractal_generator.polynomial = polynomial;
    fractal_generator.generate = &_fractal_generate;

    _init_zeros(&fractal_generator);

    return fractal_generator;
}

void free_fractal(FractalGenerator *fractal_generator)
{
    free(fractal_generator->zero_colors);
}



