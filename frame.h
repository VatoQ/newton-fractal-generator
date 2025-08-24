#ifndef FRAME_H
#define FRAME_H

#include "polynomial.h"
#include "zeros_generator.h"
#include "fractal.h"
#include <stddef.h>

typedef struct frame 
{
    const size_t flop_per_iter;
    const size_t min_flop, max_flop;
    FractalGenerator fractal_generator;
    Polynomial polynomial;
    int (*generate)(struct frame* self, const char* filename);
} Frame;

Frame make_frame(double radius,
                 int zero_count,
                 zero_pattern zero_pattern,
                 int x_res,
                 int y_res,
                 double x_root,
                 double y_root,
                 double x_range);


#endif // FRAME_H
