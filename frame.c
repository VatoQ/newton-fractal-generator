#define _POSIX_C_SOURCE 199309L

#include "frame.h"
#include "color.h"
#include "fractal.h"
#include "polynomial.h"
#include <stdlib.h>
#include <time.h>

int _frame_generate(Frame* self, const char* filename)
{
    int matrix_size = self->fractal_generator.matrix_size;
    Color* matrix = malloc(sizeof(Color) * matrix_size);


    double seconds;
    struct timespec start, end;

    clock_gettime(CLOCK_MONOTONIC, &start);
    
    int status = self->fractal_generator.generate(&self->fractal_generator,
                                                  matrix);

    clock_gettime(CLOCK_MONOTONIC, &end);


    seconds = ((double)end.tv_sec - (double)start.tv_sec) +
        ((double)end.tv_nsec - (double)start.tv_nsec) / 1.0e9;

    double flops_min = (double)self->min_flop / seconds;
    double flops_max = (double)self->max_flop / seconds;

}

Frame make_frame(double radius, 
                 int zero_count, 
                 zero_pattern zero_pattern, 
                 int x_res, 
                 int y_res, 
                 double x_root, 
                 double y_root, 
                 double x_range)
{
    Frame frame;
    frame.polynomial = new_polynomial(radius, zero_count, zero_pattern);

    frame.fractal_generator = make_fractal_generator(x_res,
                                                     y_res,
                                                     x_root,
                                                     y_root,
                                                     x_range,
                                                     &frame.polynomial);

    frame.generate = &_frame_generate;

    return frame;
}
